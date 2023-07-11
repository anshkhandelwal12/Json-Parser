#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

//cJSON library ref: https://github.com/DaveGamble/cJSON

/* Max limit of char for string */
#define STR_NULL_CHAR_LN                    (1U)

#define USERNAME_MAXCHR_LIMIT               ((20U) + STR_NULL_CHAR_LN)
#define SYSTEMNAME_MAXCHR_LIMIT             ((10U) + STR_NULL_CHAR_LN)
#define DATEFMT_MAXCHR_LIMIT                ((10U) + STR_NULL_CHAR_LN)
#define DATE_MAXCHR_LIMIT                   ((10U) + STR_NULL_CHAR_LN)
#define TIME_MAXCHR_LIMIT                   ((10U) + STR_NULL_CHAR_LN)
#define TIMEZONE_MAXCHR_LIMIT               ((10U) + STR_NULL_CHAR_LN)
#define CURRENT_CAM_NAME_MAXCHR_LIMIT       ((30U) + STR_NULL_CHAR_LN)
#define NEXT_CAM_NAME_MAXCHR_LIMIT          ((30U) + STR_NULL_CHAR_LN)
#define PREV_CAM_NAME_MAXCHR_LIMIT          ((30U) + STR_NULL_CHAR_LN)
#define ROOM_NAME_MAXCHR_LIMIT              ((30U) + STR_NULL_CHAR_LN)

typedef struct _NotificationParams
{
    unsigned short notificationId;

    char userName[USERNAME_MAXCHR_LIMIT];
    char systemName[SYSTEMNAME_MAXCHR_LIMIT];
    char date[DATE_MAXCHR_LIMIT];
    char time[TIME_MAXCHR_LIMIT];
    char timeZone[TIMEZONE_MAXCHR_LIMIT];

    char currentCamName[CURRENT_CAM_NAME_MAXCHR_LIMIT];
    char nextCamName[NEXT_CAM_NAME_MAXCHR_LIMIT];
    char prevCamName[PREV_CAM_NAME_MAXCHR_LIMIT];

    char roomName[ROOM_NAME_MAXCHR_LIMIT];

    unsigned short currentMon;
    unsigned short currentCam;

    unsigned short playbackMon;
    unsigned short playbackCam;

    unsigned short errorCode;
}NotificationParams;

typedef enum _KeyDataType
{
    TYPE_STR,
    TYPE_INT
}KeyDataType;

typedef struct _JsonKey
{
    char *keyName;                  // JSON Key name e.g. "UN"/"CMON" etc
    KeyDataType dataType;           // Key type String, Number    
    unsigned int keyMaxDataLen;     // Max data length for the key. Only applicable for string type
    void *targetVar;                // Variable address where key value will be stored
}JsonKey;

/* Write a for loop to iterate over this list and parse keys from JSON notification depending on key type*/
JsonKey jsonKeysList[]
{
    // To be populated based on JSON notifications strings
    {"CCAMN", TYPE_STR, CURRENT_CAM_NAME_MAXCHR_LIMIT, currentCamName}, 
    /* Above example means 'If key name "CCAMN" is present in JSON:
        - Parse it's value in string form 
        - Max lenght of value can be CURRENT_CAM_NAME_MAXCHR_LIMIT bytes
        - Store value in variable 
    */
    {"CMON", TYPE_INT, 0, &currentMon},  
    // Expand this list based on the unique keys for all notifications
};

#endif //__JSON_PARSER_H__

