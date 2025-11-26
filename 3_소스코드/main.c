
#include <stdio.h>
#include <string.h>

#define MAX_PROCS 20
#define NAME_LEN 32

typedef struct {
    char name[NAME_LEN];
    int time;
    int start;
    int finish;
} Process;

void input_processes(Process procs[], int *n);
void simulate_sequence(Process procs[], int n);
void copy_processes(Process src[], Process dest[], int n);
void sort_by_time(Process procs[], int n);
double average_completion_time(Process procs[], int n);

int main() {
    Process procs[MAX_PROCS];
    Process procs_opt[MAX_PROCS];
    int n = 0;

    printf("=== 공정 순서 시뮬레이터 ===\n");
    input_processes(procs, &n);

    printf("\n>> 입력 순서대로 시뮬레이션 결과\n");
    simulate_sequence(procs, n);
    double avg_user = average_completion_time(procs, n);
    printf("평균 완료 시간(입력 순서): %.2f 분\n", avg_user);

    copy_processes(procs, procs_opt, n);
    sort_by_time(procs_opt, n);

    printf("\n>> SPT(처리시간 짧은 순서)로 정렬한 시뮬레이션 결과\n");
    simulate_sequence(procs_opt, n);
    double avg_opt = average_completion_time(procs_opt, n);
    printf("평균 완료 시간(SPT): %.2f 분\n", avg_opt);

    printf("\n=== 비교 ===\n");
    printf("입력 순서 평균: %.2f 분 | SPT 평균: %.2f 분\n", avg_user, avg_opt);
    if (avg_opt < avg_user) {
        printf("=> SPT가 평균 완료시간을 %.2f 분만큼 개선합니다.\n", avg_user - avg_opt);
    } else {
        printf("=> 입력한 순서가 이미 효율적이거나 동일합니다.\n");
    }

    return 0;
}

void input_processes(Process procs[], int *n) {
    int i;
    printf("공정 개수 입력 (최대 %d): ", MAX_PROCS);
    scanf("%d", n);
    if (*n < 1) *n = 1;
    if (*n > MAX_PROCS) *n = MAX_PROCS;

    for (i = 0; i < *n; ++i) {
        printf("공정 %d 이름: ", i+1);
        scanf("%s", procs[i].name);
        printf("공정 %d 소요시간(분): ", i+1);
        scanf("%d", &procs[i].time);
        procs[i].start = -1;
        procs[i].finish = -1;
    }
}

void simulate_sequence(Process procs[], int n) {
    int time = 0;
    for (int i = 0; i < n; ++i) {
        procs[i].start = time;
        time += procs[i].time;
        procs[i].finish = time;
        printf("공정 %d: %-10s | 시작: %3d 분, 소요: %3d 분, 완료: %3d 분\n",
               i+1, procs[i].name, procs[i].start, procs[i].time, procs[i].finish);
    }
    printf("총 소요 시간: %d 분\n", time);
}

void copy_processes(Process src[], Process dest[], int n) {
    for (int i = 0; i < n; ++i) {
        strcpy(dest[i].name, src[i].name);
        dest[i].time = src[i].time;
        dest[i].start = src[i].start;
        dest[i].finish = src[i].finish;
    }
}

void sort_by_time(Process procs[], int n) {
    for (int i = 0; i < n-1; ++i) {
        int min_idx = i;
        for (int j = i+1; j < n; ++j) {
            if (procs[j].time < procs[min_idx].time) min_idx = j;
        }
        if (min_idx != i) {
            Process tmp = procs[i];
            procs[i] = procs[min_idx];
            procs[min_idx] = tmp;
        }
    }
}

double average_completion_time(Process procs[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += procs[i].finish;
    return sum / n;
}

    
    
    return 0;
}
