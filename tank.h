#pragma once

#include <math.h>

#include "structs.h"
#include "const.h"

void shoot(Tanque *t);
void stats(Tanque *t);

void canonDown(Tanque *t);
void canonUp(Tanque *t);
void towerRight(Tanque *t);
void towerLeft(Tanque *t);
void tankLeft(Tanque *t);
void tankRight(Tanque *t);
void tankFront(Tanque *t);
void tankBack(Tanque *t);
void tankSlowDown(Tanque *t);
void reloadCooldown(Tanque *t);
void powerCooldown(Tanque *t);
void speedCooldown(Tanque *t);

void updateTank(Tanque *t);
void updateCooldowns(Tanque *t);
void updatePosition(Tanque *t);
void updateBullets(Tanque *t);
void updateBullet(Bullet *b);