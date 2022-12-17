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
typedef enum {SET_FALSE_IN_LABELS, SEND_CHOSEN_DATA_TYPE, ADD_NEW_NOTE,
              GET_TOURNS, GET_STAGES, GET_TEAM_TYPES, GET_CLUBS, GET_STADIUMS,
              UPDATE, DELETE} REQUEST_TYPE;
typedef enum {READ, WRITE} NOTE_VIEW_TYPE;
typedef enum {EXIST, NOT_EXIST} EXISTANCE_STATUS;
#endif // ENUMS_H
