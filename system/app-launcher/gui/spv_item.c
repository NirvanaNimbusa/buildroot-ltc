#include<stdio.h>
#include<string.h>

#include "spv_common.h"
#include "spv_item.h"
#include "spv_language_res.h"
#include "spv_debug.h"

#ifndef GET_ARRAY_LENGTH
#define GET_ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
#endif

	//video setting item
DIALOGITEM g_video_items[] = {
    {
        ID_VIDEO_RESOLUTION, ITEM_TYPE_SETUP_PARAM,
        STRING_VIDEO_RESOLUTION, STRING_1088,
        //{STRING_3264, STRING_2880, STRING_2048, STRING_1920, STRING_1472, STRING_1088, STRING_768}, 7 
        {STRING_1920, STRING_1088, STRING_768}, 3 
    },
    {
        ID_VIDEO_RECORD_MODE, ITEM_TYPE_SETUP_PARAM,
        STRING_VIDEO_RECORDMODE, STRING_NORMAL,
        {STRING_NORMAL, STRING_TIMELAPSED_IMAGE}, 2
    },
    //{
    //    ID_VIDEO_PREVIEW, ITEM_TYPE_SETUP_PARAM,
    //    STRING_VIDEO_PREVIEW, STRING_PANORAMA_ROUND,
    //    {STRING_PANORAMA_ROUND, STRING_PANORAMA_EXPAND, STRING_TWO_SEGMENT, 
	//	 STRING_THREE_SEGMENT, STRING_FOUR_SEGMENT, STRING_ROUND, STRING_VR}, 7 
    //},
    {
        ID_VIDEO_LOOP_RECORDING, ITEM_TYPE_SETUP_PARAM,
        STRING_LOOP_RECORDING, STRING_3_MINUTES,
        {STRING_OFF, STRING_1_MINUTE, STRING_3_MINUTES, STRING_5_MINUTES}, 4 
    },
    {
        ID_VIDEO_TIMELAPSED_IMAGE, ITEM_TYPE_SETUP_PARAM,
        STRING_TIMELAPSED_IMAGE, STRING_OFF,
        {STRING_OFF, STRING_1_SECONDS, STRING_2_SECONDS, STRING_3_SECONDS, 
		 STRING_5_SECONDS, STRING_10_SECONDS}, 6 
    },
    //{
    //    ID_VIDEO_HIGH_SPEED, ITEM_TYPE_SETUP_PARAM,
    //    STRING_HIGH_SPEED, STRING_OFF,
    //    {STRING_OFF, STRING_ON}, 2 
    //},
    {
        ID_VIDEO_WDR, ITEM_TYPE_SETUP_PARAM,
        STRING_WDR, STRING_OFF,
        {STRING_OFF, STRING_ON}, 2 
    },
    {
        ID_VIDEO_EV, ITEM_TYPE_SETUP_PARAM,
        STRING_EV_COMPENSATION, STRING_ZERO,
        {STRING_POS_2P0, STRING_POS_1P5, STRING_POS_1P0, STRING_POS_0P5, STRING_ZERO,
		 STRING_NEG_0P5, STRING_NEG_1P0, STRING_NEG_1P5, STRING_NEG_2P0}, 9 
    },
    {
        ID_VIDEO_GSENSOR, ITEM_TYPE_SETUP_PARAM,
        STRING_GSENSOR, STRING_OFF,
        {STRING_OFF, STRING_HIGH, STRING_MEDIUM, STRING_LOW}, 4
    },
    {
        ID_VIDEO_RECORD_AUDIO, ITEM_TYPE_SETUP_PARAM,
        STRING_RECORD_AUDIO, STRING_ON,
        {STRING_OFF, STRING_ON}, 2 
    },
    {
        ID_VIDEO_DATE_STAMP, ITEM_TYPE_SETUP_PARAM,
        STRING_DATE_STAMP, STRING_ON,
        {STRING_OFF, STRING_ON}, 2 
    },
    {
        ID_VIDEO_RESET, ITEM_TYPE_NORMAL,
        STRING_RESTORE_DEFAULT, 0,
        {0}, 0 
    },
};

DIALOGITEM g_photo_items[] = {
    {
        ID_PHOTO_RESOLUTION, ITEM_TYPE_SETUP_PARAM,
        STRING_PHOTO_RESOLUTION, STRING_1088,
        //{STRING_16M, STRING_10M, STRING_8M, STRING_4M}, 4
        {STRING_1088}, 1
    },
    {
        ID_PHOTO_CAPTUREMODE, ITEM_TYPE_SETUP_PARAM,
        STRING_PHOTO_CAPTUREMODE, STRING_NORMAL,
        {STRING_NORMAL, STRING_MODE_TIMER, STRING_MODE_AUTO, STRING_MODE_SEQUENCE}, 4
    },
    //{
    //    ID_PHOTO_PREVIEW, ITEM_TYPE_SETUP_PARAM,
    //    STRING_PHOTO_PREVIEW, STRING_PANORAMA_ROUND,
    //    {STRING_PANORAMA_ROUND, STRING_PANORAMA_EXPAND, STRING_TWO_SEGMENT, 
	//	 STRING_THREE_SEGMENT, STRING_FOUR_SEGMENT, STRING_ROUND, STRING_VR}, 7 
    //},
    {
        ID_PHOTO_MODE_TIMER, ITEM_TYPE_SETUP_PARAM,
        STRING_MODE_TIMER, STRING_OFF,
        {STRING_OFF, STRING_2_SECONDS, STRING_5_SECONDS, STRING_10_SECONDS}, 4
    },
    {
        ID_PHOTO_MODE_AUTO, ITEM_TYPE_SETUP_PARAM,
        STRING_MODE_AUTO, STRING_OFF,
        {STRING_OFF, STRING_3_SECONDS, STRING_10_SECONDS, STRING_15_SECONDS,
		 STRING_20_SECONDS, STRING_30_SECONDS}, 6
    },
    {
        ID_PHOTO_MODE_SEQUENCE, ITEM_TYPE_SETUP_PARAM,
        STRING_MODE_SEQUENCE, STRING_OFF,
        {STRING_OFF, STRING_3PS, STRING_5PS, STRING_7PS, STRING_10PS}, 5
    },
    {
        ID_PHOTO_QUALITY, ITEM_TYPE_SETUP_PARAM,
        STRING_QUALITY, STRING_FINE,
        {STRING_FINE, STRING_NORMAL, STRING_ECONOMY}, 3
    },
    {
        ID_PHOTO_SHARPNESS, ITEM_TYPE_SETUP_PARAM,
        STRING_SHARPNESS, STRING_NORMAL,
        {STRING_NORMAL, STRING_STRONG, STRING_SOFT}, 3
    },
    {
        ID_PHOTO_WHITE_BALANCE, ITEM_TYPE_SETUP_PARAM,
        STRING_WHITE_BALANCE, STRING_AUTO,
        {STRING_AUTO, STRING_DAYLIGHT, STRING_CLOUDY, STRING_TUNGSTEN, STRING_FLUORESCENT}, 5
    },
    {
        ID_PHOTO_COLOR, ITEM_TYPE_SETUP_PARAM,
        STRING_COLOR, STRING_COLOR,
        {STRING_COLOR, STRING_BLACK_AND_WHITE}, 2
    },
    {
        ID_PHOTO_ISO_LIMIT, ITEM_TYPE_SETUP_PARAM,
        STRING_ISO_LIMIT, STRING_AUTO,
        {STRING_AUTO, STRING_800, STRING_400, STRING_200, STRING_100}, 5
    },
    {
        ID_PHOTO_EV, ITEM_TYPE_SETUP_PARAM,
        STRING_EV_COMPENSATION, STRING_ZERO,
        {STRING_POS_2P0, STRING_POS_1P5, STRING_POS_1P0, STRING_POS_0P5, STRING_ZERO,
		 STRING_NEG_0P5, STRING_NEG_1P0, STRING_NEG_1P5, STRING_NEG_2P0}, 9 
    },
    {
        ID_PHOTO_ANTI_SHAKING, ITEM_TYPE_SETUP_PARAM,
        STRING_ANTI_SHAKING, STRING_OFF,
        {STRING_OFF, STRING_ON}, 2
    },
    {
        ID_PHOTO_DATE_STAMP, ITEM_TYPE_SETUP_PARAM,
        STRING_DATE_STAMP, STRING_OFF,
        {STRING_OFF, STRING_ON}, 2 
    },
    {
        ID_PHOTO_RESET, ITEM_TYPE_NORMAL,
        STRING_RESTORE_DEFAULT, 0,
        {0}, 0 
    },
};

DIALOGITEM g_setup_items[] = {
    {
        ID_SETUP_LANGUAGE, ITEM_TYPE_SETUP_PARAM,
        STRING_LANGUAGE, STRING_CHINESE,
        {STRING_ENGLISH, STRING_CHINESE, STRING_CHINESE_TRADITIONAL, STRING_FRENCH,
		 STRING_ESPANISH, STRING_ITALIAN, STRING_PORTUGUESE, STRING_GERMAN,
		 STRING_RUSSIAN}, 9
    },
    {
        ID_SETUP_WIFI_MODE, ITEM_TYPE_SETUP_PARAM,
        STRING_WIFI_MODE, STRING_OFF,
        {STRING_OFF, STRING_DIRECT}, 2
    },
    {
        ID_SETUP_LED_FREQ, ITEM_TYPE_SETUP_PARAM,
        STRING_FREQUENCY, STRING_AUTO,
        {STRING_AUTO, STRING_50HZ, STRING_60HZ}, 3
    },
    //{
    //    ID_SETUP_LED, ITEM_TYPE_SETUP_PARAM,
    //    STRING_LED, STRING_ON,
    //    {STRING_OFF, STRING_ON}, 2
    //},
    {
        ID_SETUP_CARDV_MODE, ITEM_TYPE_SETUP_PARAM,
        STRING_CARDV_MODE, STRING_OFF,
        {STRING_OFF, STRING_ON}, 2
    },
    {
        ID_SETUP_PARKING_GUARD, ITEM_TYPE_SETUP_PARAM,
        STRING_PARKING_GUARD, STRING_OFF,
        {STRING_OFF, STRING_ON}, 2
    },
    {
        ID_SETUP_IMAGE_ROTATION, ITEM_TYPE_SETUP_PARAM,
        STRING_IMAGE_ROTATION, STRING_OFF,
        {STRING_OFF, STRING_ON}, 2
    },
    {
        ID_SETUP_DATE_TIME, ITEM_TYPE_NORMAL,
        STRING_TIME_DATE_SETTING, 0,
        {0}, 0
    },
    {
        ID_SETUP_VOLUME, ITEM_TYPE_SETUP_PARAM,
        STRING_VOLUME, STRING_70P,
        {STRING_10P, STRING_20P, STRING_30P, STRING_40P, STRING_50P, STRING_60P,
		 STRING_70P, STRING_80P, STRING_90P, STRING_100P}, 10
    },
    {
        ID_SETUP_KEY_TONE, ITEM_TYPE_SETUP_PARAM,
        STRING_KEY_TONE, STRING_ON,
        {STRING_OFF, STRING_ON}, 2
    },
    {
        ID_SETUP_AUTO_SLEEP, ITEM_TYPE_SETUP_PARAM,
        STRING_AUTO_SLEEP, STRING_30_SECONDS,
        {STRING_OFF, STRING_10_SECONDS, STRING_20_SECONDS, STRING_30_SECONDS}, 4
    },
    {
        ID_SETUP_AUTO_POWER_OFF, ITEM_TYPE_SETUP_PARAM,
        STRING_AUTO_POWER_OFF, STRING_5_MINUTES,
        {STRING_OFF, STRING_1_MINUTE, STRING_3_MINUTES, STRING_5_MINUTES}, 4
    },
    {
        ID_SETUP_DELAYED_SHUTDOWN, ITEM_TYPE_SETUP_PARAM,
        STRING_DELAYED_SHUTDOWN, STRING_10_SECONDS,
        {STRING_OFF, STRING_10_SECONDS, STRING_20_SECONDS, STRING_30_SECONDS}, 4
    },
    {
        ID_SETUP_FORMAT, ITEM_TYPE_NORMAL,
        STRING_FORMAT, 0,
        {0}, 0
    },
    {
        ID_SETUP_CAMERA_RESET, ITEM_TYPE_NORMAL,
        STRING_CAMERA_RESET, 0,
        {0}, 0
    },
    {
        ID_SETUP_VERSION, ITEM_TYPE_NORMAL,
        STRING_VERSION, 0,
        {0}, 0
    },
};

/*  
DIALOGITEM g_display_items[] = {
    {
        ID_DISPLAY_HEADER, ITEM_TYPE_HEADER | ITEM_STATUS_SECONDARY,
        STRING_DISPLAY, STRING_BACK,
        {0}, 0
    },
    {
        ID_DISPLAY_SLEEP, ITEM_TYPE_SETUP_PARAM,
        STRING_SLEEP, STRING_NEVER,
        {STRING_3_MINUTES, STRING_5_MINUTES, STRING_10_MINUTES, STRING_OFF}, 4
    },
    {
        ID_DISPLAY_BRIGHTNESS, ITEM_TYPE_SETUP_PARAM,
        STRING_BRIGHTNESS, STRING_HIGH,
        {STRING_HIGH, STRING_MEDIUM, STRING_LOW}, 3
    }
};*/
 
DIALOGITEM g_date_time_items[] = {
    //{
    //    ID_DATE_TIME_HEADER, ITEM_TYPE_HEADER | ITEM_STATUS_SECONDARY,
    //    STRING_DATE_TIME, STRING_BACK,
    //    {0}, 0
    //},
    {
        ID_SETUP_DATE, ITEM_TYPE_NORMAL,
        STRING_DATE_SETTING, 0,
        {0}, 0
    },
    {
        ID_SETUP_TIME, ITEM_TYPE_NORMAL,
        STRING_TIME_SETTING, 0,
        {0}, 0
    },
};

void UpdateSetupDialogItemValue(const char *key, const char *value)
{
    int keyId = GetKeyId(key);

    if(keyId < 0)
        return;

    int i = 0;

    DIALOGITEM *pItems[5] = {g_video_items, g_photo_items, g_setup_items, g_date_time_items};

    int length[5] = {GET_ARRAY_LENGTH(g_video_items), GET_ARRAY_LENGTH(g_photo_items), GET_ARRAY_LENGTH(g_setup_items), GET_ARRAY_LENGTH(g_date_time_items)};

    for(i = 0; i < 5; i ++) {
        if(keyId < length[i]) {//found in the list
            INFO("UpdateSetupDialogItemValue, i:%d, keyId: %d\n", i, keyId);
            pItems[i][keyId].currentValue = GetStringId(value);
            return;
        } else {
            keyId = keyId - length[i];
        }
    }
    ERROR("UpdateSetupDialogItemValue failed\n");
}

int GetSettingItemsCount(int type)
{
    int count = 0;
    switch(type) {
        case TYPE_VIDEO_SETTINGS:
            count = GET_ARRAY_LENGTH(g_video_items);
            break;
        case TYPE_PHOTO_SETTINGS:
            count = GET_ARRAY_LENGTH(g_photo_items);
            break;
        case TYPE_SETUP_SETTINGS:
            count = GET_ARRAY_LENGTH(g_setup_items);
            break;
        //case TYPE_DISPLAY_SETTINGS:
        //    count = GET_ARRAY_LENGTH(g_display_items);
        //    break;
        case TYPE_DATE_TIME_SETTINGS:
            count = GET_ARRAY_LENGTH(g_date_time_items);
            break;
    }
    return count;
}