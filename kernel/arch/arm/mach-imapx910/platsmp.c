/*
 *  linux/arch/arm/mach-imapx910/platsmp.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 *  Copyright (C) 2009 Palm
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/jiffies.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/mm.h>

#include <asm/cacheflush.h>
#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/smp_scu.h>
#include <asm/smp_plat.h>
#include <asm/unified.h>
#include <asm/cp15.h>

#include <mach/imap-iomap.h>
#include <mach/power-gate.h>
#include "core.h"

#ifdef CONFIG_VFP
#include <asm/vfp.h>
#endif

#define IMAPX910_SYS_PCADDR (IO_ADDRESS(IMAP_IRAM_BASE) + 0x17f00)
#define IMAPX910_RESET_STATE	(IO_ADDRESS(SYSMGR_SYSMGR_BASE) + 0x10)
#define IMAPX910_SWIRL_POINT	0x3c017f00

static DEFINE_SPINLOCK(boot_lock);
static void __iomem *scu_base = (void __iomem *)IMAP_SCU_VA;
void __cpuinit imapx910_secondary_init(unsigned int cpu)
{
}

static unsigned long cpu_boot_phy_addr;
static void __iomem *cpu_boot_vir_addr;

static int remap_cpu_boot_addr(void)
{
	struct sysinfo i;
	int size;

	si_meminfo(&i);
	if (i.totalram * i.mem_unit < 512*1024*1024) {
		size = 511;
	} else if (i.totalram * i.mem_unit > 512*1024*1024) {
		size = 1023;
	}

	cpu_boot_phy_addr = PLAT_PHYS_OFFSET + size*1024*1024+ 0x1000;
	cpu_boot_vir_addr = ioremap(cpu_boot_phy_addr, 0x200);
	if (!cpu_boot_vir_addr) {
		printk("failed to remap cpu boot addr\n");
		return -1;
	}

	cpu_boot_vir_addr = PTR_ALIGN(cpu_boot_vir_addr, 0x100);
	return 0;
}

static int first = 0;
int __cpuinit imapx910_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	/*
	 * set synchronisation state between this boot processor
	 * and the secondary one
	 */
//	if (cpu > 1)
//		return -1;

	first++;
	if (first == 1)	{
		if (remap_cpu_boot_addr() == -1) {
			return -1;
		}
	}

	first = 2;

	spin_lock(&boot_lock);

	//imapx910_reset_core(cpu, IMAPX910_SWIRL_POINT);
	imapx910_reset_core(cpu, cpu_boot_phy_addr, cpu_boot_vir_addr);
	/* put the old boot vector back */

//	writel(virt_to_phys(imapx910_secondary_startup),
//			IMAPX910_SYS_PCADDR + cpu * 4);
	writel(virt_to_phys(imapx910_secondary_startup),
			cpu_boot_vir_addr + cpu * 4);
	smp_wmb();
	flush_cache_all();
	udelay(50);

	/*
	 * now the secondary core is starting up let it run its
	 * calibrations, then wait for it to finish
	 */
	spin_unlock(&boot_lock);
	return 0;
}

/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the system.
 */
void __init imapx910_smp_init_cpus(void)
{


	unsigned int i = -1, ncores = scu_get_core_count(scu_base);
	if (ncores > nr_cpu_ids) {
		pr_warn("SMP: %u cores greater than maximum (%u), clipping\n",
				ncores, nr_cpu_ids);
		ncores = nr_cpu_ids;
	}

	for (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);

	//set_smp_cross_call(gic_raise_softirq);

}

void __init imapx910_smp_prepare_cpus(unsigned int max_cpus)
{
	int i;
	/*
	 * Initialise the present map, which describes the set of CPUs
	 * actually populated at the present time.
	 */
	for (i = 0; i < max_cpus; i++)
		set_cpu_present(i, true);

	scu_enable(scu_base);
}

#ifdef CONFIG_HOTPLUG_CPU

static DECLARE_COMPLETION(cpu_killed);

static inline void cpu_enter_lowpower(void)     
{                                               
    unsigned int v;                             
                                                
    flush_cache_all();                          
    asm volatile (" mcr p15, 0, %1, c7, c5, 0\n"
              " mcr p15, 0, %1, c7, c10, 4\n"   
              /*                                
               * Turn off coherency             
               */                               
              " mrc p15, 0, %0, c1, c0, 1\n"    
              " bic %0, %0, #0x20\n"            
              " mcr p15, 0, %0, c1, c0, 1\n"    
              " mrc p15, 0, %0, c1, c0, 0\n"    
              " bic %0, %0, %2\n"               
              " mcr p15, 0, %0, c1, c0, 0\n"    
                : "=&r" (v)                     
                : "r"(0), "Ir"(CR_C)            
                : "cc");                        
}                                               


static inline void cpu_leave_lowpower(void)      
{                                                
    unsigned int v;                              
                                                 
    asm volatile ("mrc  p15, 0, %0, c1, c0, 0\n" 
              " orr %0, %0, %1\n"                
              " mcr p15, 0, %0, c1, c0, 0\n"     
              " mrc p15, 0, %0, c1, c0, 1\n"     
              " orr %0, %0, #0x20\n"             
              " mcr p15, 0, %0, c1, c0, 1\n"     
                : "=&r" (v)                      
                : "Ir"(CR_C)                     
                : "cc");                         
}                                                


static inline void imapx910_do_lowpower(unsigned int cpu, int *spurious)
{
	/*
	 * there is no power-control hardware on this platform, so all
	 * we can do is put the core into WFI; this is safe as the calling
	 * code will have already disabled interrupts
	 */
	for (;;) {
		/*
		 * here's the WFI
		 */
		asm(".word	0xe320f003\n"
			:
			:
			: "memory", "cc");

		/*
		 * Getting here, means that we have come out of WFI without
		 * having been woken up - this shouldn't happen
		 *
		 * Just note it happening - when we're woken, we can report
		 * its occurrence.
		 */
		(*spurious)++;
	}
}

static cpumask_t dead_cpus;
void imapx910_cpu_power_down(unsigned int cpu)
{
	uint32_t tmp;

	tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE) + 0xc4);
	writel(tmp | (1 << (cpu + 4)), IO_ADDRESS(SYSMGR_CPU_BASE) + 0xc4);

	/* reset wdt & debug */
	tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE));
	writel(tmp & ~(1 << (cpu)), IO_ADDRESS(SYSMGR_CPU_BASE + 4));
	tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE));
	writel(tmp & ~(1 << (cpu + 4)), IO_ADDRESS(SYSMGR_CPU_BASE + 4));

	/* reset cpu */
	tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE));
	writel(tmp & ~(1 << (4 + cpu)), IO_ADDRESS(SYSMGR_CPU_BASE));

	/* reset neon */
	tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE) + 0xbc);
	writel(tmp & ~(1 << cpu), IO_ADDRESS(SYSMGR_CPU_BASE) + 0xbc);

	/* turn off clock:cpu */
	tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE) + 0xc4);
	writel(tmp | (1 << cpu), IO_ADDRESS(SYSMGR_CPU_BASE) + 0xc4);
	/* turn off clock :neon */
	tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE) + 0xc8);
	writel(tmp | (1 << (cpu + 4)), IO_ADDRESS(SYSMGR_CPU_BASE) + 0xc8);

	mdelay(1);
	if (cpu > 1) {
		/*power down core */
		tmp = readl(IO_ADDRESS(SYSMGR_CPU_BASE) + 0xe4);
		writel(tmp & ~(1 << cpu), IO_ADDRESS(SYSMGR_CPU_BASE) + 0xe4);
	}
}

int imapx910_cpu_kill(unsigned int cpu)
{
	int k;

	/* this function is running on another CPU than the offline target,
	 * here we need wait for shutdown code in platform_cpu_die() to
	 * finish before asking SoC-specific code to power off the CPU core.
	 */
	for (k = 0; k < 1000; k++) {
		if (cpumask_test_cpu(cpu, &dead_cpus)) {
			imapx910_cpu_power_down(cpu);
			return 1;
		}

		mdelay(1);
	}
	return 1;
}


/*
 * platform-specific code to shutdown a CPU
 *
 * Called with IRQs disabled
 */
void imapx910_cpu_die(unsigned int cpu)
{
	/* hardware shutdown code running on the CPU that is being offlined */
	flush_cache_all();
	dsb();

	/* notify platform_cpu_kill() that hardware shutdown is finished */
	cpumask_set_cpu(cpu, &dead_cpus);

	/* wait for SoC code in platform_cpu_kill() to shut off CPU core
	 * power. CPU bring up starts from the reset vector.
	 */
	while (1) {
		dsb();
		wfi();
	}
}

int imapx910_cpu_disable(unsigned int cpu)                           
{                                                                    
	cpumask_clear_cpu(cpu, &dead_cpus);
    /*                                                               
     * we don't allow CPU 0 to be shutdown (it is still too special  
     * e.g. clock tick interrupts)                                   
     */                                                              
    return cpu == 0 ? -EPERM : 0;                                    
}                                                                 

#endif


struct smp_operations imapx910_smp_ops __initdata = { 
	.smp_init_cpus		= imapx910_smp_init_cpus,
	.smp_prepare_cpus   = imapx910_smp_prepare_cpus,  
	.smp_secondary_init = imapx910_secondary_init,    
	.smp_boot_secondary = imapx910_boot_secondary,    
#ifdef CONFIG_HOTPLUG_CPU                          
	.cpu_kill       = imapx910_cpu_kill,              
	.cpu_die        = imapx910_cpu_die,               
	.cpu_disable	= imapx910_cpu_disable,
#endif                                             
};                                                 
