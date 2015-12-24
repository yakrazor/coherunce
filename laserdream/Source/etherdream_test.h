#include "etherdream.h"
#include <math.h>

uint16_t colorsin(float pos) {
	int res = (sin(pos) + 1) * 32768;
	if (res < 0) return 0;
	if (res > 65535) return 65535;
	return res;
}

void fill_circle(etherdream_point* points, int num_points, float phase, int mode) {
	int i;
	for (i = 0; i < num_points; i++) {
		struct etherdream_point *pt = &points[i];
		float ip = (float)i * 2.0 * M_PI / (float)num_points;
		float ipf = fmod(ip + phase, 2.0 * M_PI);;

		switch (mode) {
		default:
		case 0: {
			float cmult = .05 * sin(30 * (ip - phase/3));
			pt->x = sin(ip) * 20000 * (1 + cmult);
			pt->y = cos(ip) * 20000 * (1 + cmult);
			break;
		}
		case 1: {
			float cmult = .10 * sin(10 * (ip - phase/3));
			pt->x = sin(ip) * 20000 * (1 + cmult);
			pt->y = cos(ip) * 20000 * (1 + cmult);
			break;
			/* XXX broken */
/*
			float R = 3;
			float r = 5;
			pt->x = 2000 * ((R-r)*cos(ip+phase) + r*cos((R-r)*ip/r));
			pt->y = 2000 * ((R-r)*sin(ip+phase) - r*sin((R-r)*ip/r));
			break;
*/
		}
		case 2: {
			ip *= 3;
			float R = 5;
			float r = 3;
			float D = 5;

			pt->x = 2500 * ((R-r)*cos(ip + phase) + D*cos((R-r)*ip/r));
			pt->y = 2500 * ((R-r)*sin(ip + phase) - D*sin((R-r)*ip/r));
			break;
		}
		case 3: {
			int n = 5;
			float R = 5 * cos(M_PI/n) / cos(fmod(ip, (2*M_PI/n)) - (M_PI/n));
			pt->x = 3500 * R*cos(ip+phase);
			pt->y = 3500 * R*sin(ip+phase);
			break;
		}
		case 4: {
			float Xo = sin(ip);
			pt->x = 20000 * Xo * cos(phase/4);
			pt->y = 20000 * Xo * -sin(phase/4);
			ipf = fmod(((Xo + 1) / 2.0) + phase / 3, 1.0) * 2 * M_PI;
		}
		}

		pt->r = colorsin(ipf);
		pt->g = colorsin(ipf + (2.0 * M_PI / 3.0));
		pt->b = colorsin(ipf + (4.0 * M_PI / 3.0));
/*
		if (ipf < 2.0 * M_PI / 3.0) {
			pt->r = 65535;
			pt->g = pt->b = 0;
		} else if (ipf < 4.0 * M_PI / 3.0) {
			pt->g = 65535;
			pt->r = pt->b = 0;
		} else {
			pt->b = 65535;
			pt->r = pt->g = 0;
		}
*/
	}
}