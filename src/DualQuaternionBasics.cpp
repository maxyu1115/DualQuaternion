//
// Created by Max on 10/11/2020.
//

#include "DualQuaternionBasics.h"

void dq_add(dq_t out, const dq_t p, const dq_t q) {
    out[0] = p[0] + q[0];
    out[1] = p[1] + q[1];
    out[2] = p[2] + q[2];
    out[3] = p[3] + q[3];
    out[4] = p[4] + q[4];
    out[5] = p[5] + q[5];
    out[6] = p[6] + q[6];
    out[7] = p[7] + q[7];
}

void dq_minus(dq_t out, const dq_t p, const dq_t q) {
    out[0] = p[0] - q[0];
    out[1] = p[1] - q[1];
    out[2] = p[2] - q[2];
    out[3] = p[3] - q[3];
    out[4] = p[4] - q[4];
    out[5] = p[5] - q[5];
    out[6] = p[6] - q[6];
    out[7] = p[7] - q[7];
}

void dq_scale(dq_t out, float c, const dq_t p) {
    out[0] = c * p[0];
    out[1] = c * p[1];
    out[2] = c * p[2];
    out[3] = c * p[3];
    out[4] = c * p[4];
    out[5] = c * p[5];
    out[6] = c * p[6];
    out[7] = c * p[7];
}

void dq_conj_star(dq_t out, const dq_t p) {
    out[0] = -p[0];
    out[1] = -p[1];
    out[2] = -p[2];
    out[3] = p[3];
    out[4] = -p[4];
    out[5] = -p[5];
    out[6] = -p[6];
    out[7] = p[7];
}

void dq_conj_bar(dq_t out, const dq_t p) {
    out[0] = p[0];
    out[1] = p[1];
    out[2] = p[2];
    out[3] = p[3];
    out[4] = -p[4];
    out[5] = -p[5];
    out[6] = -p[6];
    out[7] = -p[7];
}

void dq_conj_cross(dq_t out, const dq_t p) {
    out[0] = -p[0];
    out[1] = -p[1];
    out[2] = -p[2];
    out[3] = p[3];
    out[4] = p[4];
    out[5] = p[5];
    out[6] = p[6];
    out[7] = -p[7];
}

void q_mult(q_t out, const q_t p, const q_t q) {
    out[0] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];
    out[1] = -p[0] * q[2] + p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
    out[2] = p[0] * q[1] - p[1] * q[0] + p[2] * q[3] + p[3] * q[2];
    out[3] = -p[0] * q[0] - p[1] * q[1] - p[2] * q[2] + p[3] * q[3];
}

void q_add(q_t out, const q_t p, const q_t q) {
    out[0] = p[0] + q[0];
    out[1] = p[1] + q[1];
    out[2] = p[2] + q[2];
    out[3] = p[3] + q[3];
}

void dq_mult(dq_t out, const dq_t p, const dq_t q) {
    q_mult(out, p, q);

    float out2[4];
    q_mult(&out[4], p, &q[4]);
    q_mult(out2, &p[4], q);
    q_add(&out[4], &out[4], out2);
}

void dq_sandwhich_map(dq_t out, const dq_t Q, const dq_t p) {
    dq_t conj, temp;
    dq_conj_cross(conj, Q);
    dq_mult(temp, Q, p);
    dq_mult(out, temp, conj);
}


float dq_dot(float * dual, const dq_t p, const dq_t q) {
    dq_t ans, temp1, temp2, conjp, conjq;

    dq_conj_star(conjp, p);
    dq_conj_star(conjq, q);

    dq_mult(temp1, conjq, p);
    dq_mult(temp2, conjp, q);

    dq_add(ans, temp1, temp2);

    * dual = ans[7] * 0.5f;
    return ans[3] * 0.5f;
}