#ifndef _STUDENT_IOCTL_H_
#define _STUDENT_IOCTL_H_

#include <linux/ioctl.h>

#define STUDENT_MAGIC   'S'

struct student_ioctl {
    int id;
    char name[16];
};

#define STUDENT_ADD        _IOW(STUDENT_MAGIC, 1, struct student_ioctl)
#define STUDENT_DEL        _IOW(STUDENT_MAGIC, 2, int)
#define STUDENT_QUERY_GRADE  _IOWR(STUDENT_MAGIC, 4, int)
#define STUDENT_QUERY_COLLEGE _IOWR(STUDENT_MAGIC, 5, int)

struct student_score_ioctl {
    int id;
    int score;
};

#define STUDENT_SUBMIT_SCORE _IOW(STUDENT_MAGIC, 6, struct student_score_ioctl)
#define STUDENT_QUERY_TOP _IOR(STUDENT_MAGIC, 7, struct student_score_ioctl)

#endif
