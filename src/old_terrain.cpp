
//        float max_humidity = 1;
#if 0
            float max_rot = 0.15;
            if (d->rot > max_rot) {
                d->rot = max_rot;
            } else if (d->rot < -max_rot) {
                d->rot = -max_rot;
            }
#endif



#if 0
            if (d->weight > 5) {
                d->weight = 5;
            }
            if (d->weight > 3) {
                d->weight = 3;
                wind_speed = 0.1;
            }
            if (d->weight > 2) {
                wind_speed = 0.2;
            }
            if (d->weight > 1) {
                wind_speed = 0.3;
            }
            if (d->weight > 0.5) {
                wind_speed = 0.5;
            }
#endif

//            d->velocity = d->velocity.rotate(d->rot);
#if 0
            int16_t x = mod(d->at.x, MAP_WIDTH);
            int16_t y = mod(d->at.y, MAP_WIDTH);

            auto h = get_humidity(x, y);
                d->rot *= 2;
                wind_speed = 2.10;
                d->weight *= 0.95;
#endif












#if 0
            int16_t nx = mod(new_at.x, MAP_WIDTH);
            int16_t ny = mod(new_at.y, MAP_WIDTH);

            int16_t collision = 0;

            for (auto dx = -MAX_DIST; dx < MAX_DIST; dx++) {
                for (auto dy = -MAX_DIST; dy < MAX_DIST; dy++) {
                    float cx = nx + dx;
                    auto cy = ny + dy;
                    if (DISTANCE(nx, ny, cx, cy) > d->weight) {
                        continue;
                    }

                    auto ix = mod(cx, MAP_WIDTH);
                    auto iy = mod(cy, MAP_WIDTH);

                    auto odi = droplet_map[ix][iy];
                    if (!odi) {
                        continue;
                    }

                    if (odi != di) {
                        collision = odi;
                        break;
                    }
                }
            }

            if (collision) {
//CON("collision");
                auto A = d;
                auto B = &droplets[collision];
                auto A_at = A->at;
                auto B_at = B->at;

                if (fabs(A_at.x - B_at.x) > MAP_WIDTH / 2) {
                    if (A_at.x > B_at.x) {
                        B_at.x += MAP_WIDTH;
                    } else {
                        B_at.x -= MAP_WIDTH;
                    }
                }

                if (fabs(A_at.y - B_at.y) > MAP_WIDTH / 2) {
                    if (A_at.y > B_at.y) {
                        B_at.y += MAP_WIDTH;
                    } else {
                        B_at.y -= MAP_WIDTH;
                    }
                }

                {
                    fpoint normal_A = fsub(B->at, A->at);
                    fpoint normal_B = normal_A;

                    /*
                    * Normal vector is a line between the two center of masses.
                    * Tangent vector is at 90 degrees to this.
                    */
                    fpoint normal_A_unit = funit(normal_A);
                    fpoint tangent_A_unit = { -normal_A_unit.y, normal_A_unit.x };

                    fpoint normal_B_unit = funit(normal_B);
                    fpoint tangent_B_unit = { -normal_B_unit.y, normal_B_unit.x };

                    float mA = A->weight;
                    float mB = A->weight;

                    fpoint vA = A->velocity;
                    fpoint vB = B->velocity;

                    /*
                    * Project the velocity onto the normal vectors.
                    */
                    float normal_A_len = fdot(normal_A_unit, vA);
                    float normal_B_len = fdot(normal_B_unit, vB);

                    float tangent_A_len = fdot(tangent_A_unit, vA);
                    float tangent_B_len = fdot(tangent_B_unit, vB);

                    /*
                    * Tangent velocity doesn't change.after collision.
                    */
                    float tangent_A_velocity = tangent_A_len;
                    float tangent_B_velocity = tangent_B_len;

                    /*
                    * Do one dimensional elastic collision.
                    */
                    float normal_A_velocity =
                        (normal_A_len*(mA - mB) + 2.0 * mB*normal_B_len) / (mA + mB);

                    float normal_B_velocity =
                        (normal_B_len*(mB - mA) + 2.0 * mA*normal_A_len) / (mA + mB);

#if 0
                    if (normal_A_velocity <= 0) {
                        normal_A_velocity = 0.1;
                    }
                    if (normal_B_velocity <= 0) {
                        normal_B_velocity = 0.1;
                    }
#endif

                    fpoint normal_velocity_A  = fmul(normal_A_velocity, normal_A_unit);
                    fpoint tangent_velocity_A = fmul(tangent_A_velocity, tangent_A_unit);

                    fpoint normal_velocity_B  = fmul(normal_B_velocity, normal_B_unit);
                    fpoint tangent_velocity_B = fmul(tangent_B_velocity, tangent_B_unit);

                    normal_velocity_A = fmul(COLLISION_ELASTICITY, normal_velocity_A);
                    normal_velocity_B = fmul(COLLISION_ELASTICITY, normal_velocity_B);
                    tangent_velocity_A = fmul(TANGENT_ELASTICITY, tangent_velocity_A);
                    tangent_velocity_B = fmul(TANGENT_ELASTICITY, tangent_velocity_B);

                    A->velocity.x = normal_velocity_A.x + tangent_velocity_A.x;
                    A->velocity.y = normal_velocity_A.y + tangent_velocity_A.y;

                    B->velocity.x = normal_velocity_B.x + tangent_velocity_B.x;
                    B->velocity.y = normal_velocity_B.y + tangent_velocity_B.y;

#if 0
                    if (A->weight > B->weight) {
                        A->weight *= 1.01;
                        B->weight *= 0.99;

                        B->velocity = A->velocity;
                        B->rot = A->rot;
                    } else {
                        B->weight *= 1.01;
                        A->weight *= 0.99;
                        A->velocity = B->velocity;
                        A->rot = B->rot;
                    }
                }
#endif

                // A->velocity = B->velocity;
                if (distance(A->at, B->at) < A->weight + B->weight) {
                    A->velocity = A->at - B->at;
                    A->velocity /= 10.0;
                   B->velocity = B->at - A->at;
                    A->at = A->at + A->velocity;
                    B->at = B->at + B->velocity;
                } else {
                    B->velocity = normal(B->at - A->at);
                    A->velocity = normal(A->at - B->at);
                    A->rot -= B->rot;
                    B->rot += A->rot;
                }

//                A->velocity = A->velocity.rotate(A->rot);
//                A->velocity *= 0.10;
//                new_at = A->at + A->velocity * wind_speed;
//                A->at = new_at;
            } else {
                d->at = new_at;
            }
#endif




#if 0
if (random_range(0, 100) < 50) {
d->weight *= 0.95;
}
#endif

#if 0
            if (d->weight < 0.01) {
                place_drop(di, 2);
            }
#endif

#if 0
            if (new_map[nx][ny] < 5)  {
                // over deep water
                if (random_range(0, 100) < 20) {
                    d->weight *= 1.02;
                    d->velocity *= 0.80;
                }
            } else if (new_map[nx][ny] < 15)  {
                // over water
            } else if (new_map[nx][ny] < 90)  {
                // over grass
                if (random_range(0, 100) < 50) {
                    d->velocity = d->velocity.rotate(0.15);
                    auto delta = d->weight * 0.5;
                    deposit_water(point(nx, ny), delta);
                    d->weight -= delta;
              }
            } else {
                // over nountains
                if (random_range(0, 100) < 20) {
                    d->velocity = d->velocity.rotate(-0.11);
                    auto delta = d->weight * 0.5;
                    deposit_water(point(nx, ny), delta);
                    d->weight -= delta;
                }
            }
            d->rot += d->weight / 10.0;
            d->at.x += 0.5;
#endif

    void place_drop (int di, int pass)
    {
        auto d = &droplets[di];
        int tries = 0;

        d->weight = 20.0;
        for (;;) {
#if 0
redo:
#endif
            d->at.x = random_range(0, MAP_WIDTH);
            d->at.y = gauss(MAP_WIDTH / 2, 40);

            if (d->at.y < 0) {
                d->at.y = 0;
            }
            if (d->at.y >= MAP_WIDTH) {
                d->at.y = MAP_WIDTH - 1;
            }

            int x = (int)d->at.x;
            int y = (int)d->at.y;

            int ix = mod(x, MAP_WIDTH);
            int iy = mod(y, MAP_WIDTH);

            if (pass == 1) {
                if ((tries++ < 1000) && (new_map[ix][iy] > 5)) {
                    continue;
                }
            } else {
                if (random_range(0, 100) < 80) {
                    if (humidity[ix][iy] <= 1.0) {
                        continue;
                    }
                    if (humidity[ix][iy] >= 2.0) {
                        continue;
                    }

                    d->at.x = gauss(ix, 20.0);
                    d->at.y = gauss(iy, 20.0);
                    x = (int)d->at.x;
                    y = (int)d->at.y;
                    d->rot = droplets[droplet_map[x][y]].rot;
                    d->velocity = droplets[droplet_map[x][y]].velocity;
                } else {
                    if ((tries++ < 1000) && (new_map[ix][iy] > 5)) {
                        continue;
                    }
                }
            }

#if 0
            for (auto dx = -MAX_DIST; dx < MAX_DIST; dx++) {
                for (auto dy = -MAX_DIST; dy < MAX_DIST; dy++) {
                    float cx = x + dx;
                    float cy = y + dy;
                    auto ix = mod(cx, MAP_WIDTH);
                    auto iy = mod(cy, MAP_WIDTH);
                    if (droplet_map[ix][iy]) {
                        goto redo;
                    }
                }
            }

            for (auto dx = -MAX_DIST; dx < MAX_DIST; dx++) {
                for (auto dy = -MAX_DIST; dy < MAX_DIST; dy++) {
                    float cx = x + dx;
                    float cy = y + dy;
                    auto ix = mod(cx, MAP_WIDTH);
                    auto iy = mod(cy, MAP_WIDTH);
                    droplet_map[ix][iy] = di;
                }
            }
#endif

            break;
        }

        float s, c;
        float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
        sincosf(rad, &s, &c);
        d->velocity = fpoint(s, c);
//        float r = (float)random_range(0, 360);
//        d->rot = (r / 360.0) * RAD_360;
    }
