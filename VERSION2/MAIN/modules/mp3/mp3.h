#ifndef __MP3_H
#define __MP3_H

typedef enum
{
    SLIGHT = 1,
    GENERAL = 2, // Corrected typo from "GENERAl" to "GENERAL"
    SERIOUS = 3,
} MP3_broadcast_type;
void MP3_Init(void);

void MP3_broadcast(MP3_broadcast_type info);

#endif
