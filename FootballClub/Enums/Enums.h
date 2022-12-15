/***************************************************************************
 *                                                                         *
 *   Copyright (C) 11.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef ENUMS_H
#define ENUMS_H
#pragma once
typedef enum {PLAYERS, COACHES, MATCHES, GOALS, CLUB, TEAMS, AUTHO} LABEL_TYPE;
typedef enum {SET_FALSE_IN_LABELS, SEND_CHOSEN_DATA_TYPE,
              MATCH_TOURNS, MATCH_STAGES, MATCH_TEAM_TYPES, MATCH_CLUBS, MATCH_STADIUMS, MATCH_UPDATE} REQUEST_TYPE;
typedef enum {READ, MODIFY} NOTE_VIEW_TYPE;
#endif // ENUMS_H
