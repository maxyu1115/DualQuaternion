//
// Created by Max on 10/11/2020.
//

#include "DualQuaternionGeometry.h"
#include <math.h>

void dq_to_vertex(vertex out, const dq_t p) {
    out[0] = p[4];
    out[1] = p[5];
    out[2] = p[6];
}

void dq_from_vertex(dq_t out, const vertex p) {
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 1.0f;
    out[4] = p[0];
    out[5] = p[1];
    out[6] = p[2];
    out[7] = 0.0f;
}

void dq_to_vector(vector3 out, const dq_t p) {
    out[0] = p[4];
    out[1] = p[5];
    out[2] = p[6];
}

void dq_from_vector(dq_t out, const vector3 p) {
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    out[4] = p[0];
    out[5] = p[1];
    out[6] = p[2];
    out[7] = 0.0f;
}

int dq_is_point(const dq_t p) {
    return p[3]!=0.0f && p[0]==0.0f && p[1]==0.0f && p[2]==0.0f && p[7]==0.0f;
}

int dq_is_vector(const dq_t p) {
    return p[3]==0.0f && p[0]==0.0f && p[1]==0.0f && p[2]==0.0f && p[7]==0.0f;
}

int dq_is_plane(const dq_t p) {
    return p[3]==0.0f && p[4]==0.0f && p[5]==0.0f && p[6]==0.0f;
}

void dq_cr_rot_q(dq_t out, const dq_t unit, float halfAngle) {
    dq_scale(out, sinf(halfAngle), unit);
    out[3] += cosf(halfAngle);
}

void dq_cr_tran_q(dq_t out, const dq_t unit, float halfDistance) {
    dq_scale(out, halfDistance, unit);
    out[3] += 1.0f;
}
