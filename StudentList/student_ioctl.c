#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "student_ioctl.h"

int main(void)
{
    int fd = open("/dev/student", O_RDWR);
    if (fd < 0) {
        perror("open /dev/student");
        return 1;
    }

    struct student_ioctl s;

    /* 添加多条学生数据 */
    struct {
        int id;
        char name[16];
    } dataset[] = {
        {2023103111, "Alice"},
        {2022201456, "Bob"},
        {2023103122, "Carol"},
        {2022202457, "David"},
        {2024103113, "Eve"},
        {2023201789, "Frank"},
        {2023103555, "Grace"},
        {2023201333, "Heidi"},
        {2022201999, "Ivan"},
        {2024103666, "Judy"},
    };

    int n = sizeof(dataset) / sizeof(dataset[0]);
    for (int i = 0; i < n; i++) {
        s.id = dataset[i].id;
        strncpy(s.name, dataset[i].name, sizeof(s.name));
        s.name[sizeof(s.name)-1] = '\0';
        if (ioctl(fd, STUDENT_ADD, &s) < 0) {
            perror("ioctl ADD");
        }
    }

    /* 按年级查询 */
    int grade = 2023;
    ioctl(fd, STUDENT_QUERY_GRADE, &grade);

    grade = 2022;
    ioctl(fd, STUDENT_QUERY_GRADE, &grade);

    /* 按学院查询 */
    int college = 103;
    ioctl(fd, STUDENT_QUERY_COLLEGE, &college);

    college = 201;
    ioctl(fd, STUDENT_QUERY_COLLEGE, &college);

    /* 添加学生成绩数据 */
    struct student_score_ioctl score_data;
    struct {
        int id;
        int score;
    } scores[] = {
        {2023103111, 88},
        {2022201456, 95},
        {2023103122, 91},
        {2022202457, 76},
        {2024103113, 84},
        {2023201789, 90},
        {2023103555, 87},
        {2023201333, 93},
        {2022201999, 79},
        {2024103666, 89},
    };

    n = sizeof(scores) / sizeof(scores[0]);
    for (int i = 0; i < n; i++) {
        score_data.id = scores[i].id;
        score_data.score = scores[i].score;
        if (ioctl(fd, STUDENT_SUBMIT_SCORE, &score_data) < 0) {
            perror("ioctl SUBMIT_SCORE");
        }
    }

    /* 查询成绩最高的学生 */
    if (ioctl(fd, STUDENT_QUERY_TOP, &score_data) < 0) {
        perror("ioctl QUERY_TOP");
    }

    /* 修改 Alice 的成绩后查询成绩最高的学生 */
    score_data.id = 2023103111;
    score_data.score = 99;
    if (ioctl(fd, STUDENT_SUBMIT_SCORE, &score_data) < 0) {
        perror("ioctl SUBMIT_SCORE");
    }

    if (ioctl(fd, STUDENT_QUERY_TOP, &score_data) < 0) {
        perror("ioctl QUERY_TOP");
    }

    close(fd);
    return 0;
}
