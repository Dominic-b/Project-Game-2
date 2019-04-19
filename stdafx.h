#pragma once
//including SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#undef main

#include <stdio.h>//for printf and such
#include <chrono>//for a timer / stopwatch
#include <vector>

#include "menu.h"
static Menu menu;
#include "objects.h"
#include "player.h"
#include "collision.h"
static Collision collision;
#include "timer.h"
static Timer newTimer;
#include "render.h"
static Render render;
#include "event.h"
static Event event;