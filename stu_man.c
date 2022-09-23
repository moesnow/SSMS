#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
    int year;
    int month;
    int day;
};

struct StuStatus {
    char sid[15];
    char name[12];
    char phone[15];
    char address[12];
    struct Date birthday;
    char major[12];
};

#define LEN sizeof(struct StuStatus)
struct StuStatus stu[100];
int count = 0;

void load() {
    FILE *fp;
    if ((fp = fopen("stu.dat", "rb")) == NULL) //创建新文件
    {
        if ((fp = fopen("stu.dat", "wb")) == NULL) {
            printf("加载数据文件出错，无法打开文件！\n");
            exit(1);
        }
        printf("这是你第一次使用本程序，数据文件创建成功！\n");
    }
    while (!feof(fp)) {
        if (1 != fread(&stu[count], LEN, 1, fp))
            break;
        count++;
    }
    fclose(fp);
    printf("数据文件加载成功！\n");
}

void save() {
    FILE *fp;
    if ((fp = fopen("stu.dat", "wb")) == NULL) {
        printf("保存数据文件出错，无法打开文件！\n");
        exit(1);
    }
    int i;
    for (i = 0; i < count; i++) {
        if (fwrite(&stu[i], LEN, 1, fp) != 1)
            printf("保存数据文件出错，文件写错误！\n");
    }
    fclose(fp);
    printf("数据文件保存成功！\n");
    printf("感谢您使用本程序~ 再见！\n");
}

int menu_select() {
    int select;
    printf("\n\n   [学生学籍管理系统主菜单]\n");
    printf("    +--------------------+\n");
    printf("    |    1-添加记录     |\n");
    printf("    |    2-修改记录     |\n");
    printf("    |    3-删除记录     |\n");
    printf("    |    4-查询记录     |\n");
    printf("    |    5-统计记录     |\n");
    printf("    |    6-排序记录     |\n");
    printf("    |    0-退出         |\n");
    printf("    +--------------------+\n");
    for (;;) {
        printf("\n请选择(0~6):");
        scanf("%d", &select);
        if (select < 0 || select > 6)
            printf("选择有误！请重新输入\n");
        // else if ((select > 1 & select < 7) & (count == 0))
        //     printf("暂无任何数据！\n");
        else
            break;
    }
    system("clear");
    return select;
}

int sid_exist(char num[]) {
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(num, stu[i].sid) == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}

int date_valid(int year, int month, int day) {
    int valid = 0;
    //平年 0  闰年 1
    int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    //小1  大0
    int small = month == 4 || month == 6 || month == 9 || month == 11;

    if (month > 0 && month <= 12) {
        if (month == 2) {
            if (day > 0 && day <= 28 + leap) {
                valid = 1;
            }
        } else {
            if (day > 0 && day <= 31 - small) {
                valid = 1;
            }
        }
    }
    return valid;
}

void add() {
    char temp_sid[15];
    for (;;) {
        printf("学号：");
        scanf("%s", temp_sid);
        if (sid_exist(temp_sid) == 1)
            printf("学号已存在！请重新输入\n");
        else {
            strcpy(stu[count].sid, temp_sid);
            break;
        }
    }
    printf("姓名：");
    scanf("%s", stu[count].name);
    printf("联系电话：");
    scanf("%s", stu[count].phone);
    printf("家庭地址：");
    scanf("%s", stu[count].address);
    for (;;) {
        printf("生日：");
        scanf("%d%d%d", &stu[count].birthday.year, &stu[count].birthday.month, &stu[count].birthday.day);
        if (date_valid(stu[count].birthday.year, stu[count].birthday.month, stu[count].birthday.day) != 1)
            printf("生日输入有误，请重试！\n\n");
        else
            break;
    }
    printf("专业：");
    scanf("%s", stu[count].major);
    count++;
    printf("\n添加成功！\n总记录数：%d\n", count);
}

void modi_main(int i) {
    printf("\n             [请选择修改项目]\n\n");
    printf("          +------------------------+\n");
    printf("          |    1. 修改学号       |\n");
    printf("          |    2. 修改姓名       |\n");
    printf("          |    3. 修改联系方式    |\n");
    printf("          |    4. 修改家庭地址    |\n");
    printf("          |    5. 修改生日       |\n");
    printf("          |    6. 修改专业       |\n");
    printf("          |    0. 返回          |\n");
    printf("          +------------------------+\n");
    int select;
    for (;;) {
        printf("\n请选择(0~6):");
        scanf("%d", &select);
        if (select < 0 || select > 6)
            printf("选择有误！请重新输入\n");
        else
            break;
    }
    switch (select) {
    case 1:
        printf("请输入新学号：");
        for (;;) {
            scanf("%s", stu[i].sid);
            if (sid_exist(stu[i].sid) == 1)
                printf("学号已存在！请重新输入\n");
            else {
                break;
            }
        }
        printf("修改成功！");
        break;
    case 2:
        printf("请输入新姓名：");
        scanf("%s", stu[i].name);
        printf("修改成功！");
        break;
    case 3:
        printf("请输入新联系电话:");
        scanf("%s", stu[i].phone);
        printf("修改成功！");
        break;
    case 4:
        printf("请输入新家庭地址:");
        scanf("%s", stu[i].address);
        printf("修改成功！");
        break;
    case 5:
        for (;;) {
            printf("请输入新生日:");
            scanf("%d%d%d", &stu[i].birthday.year, &stu[i].birthday.month, &stu[i].birthday.day);
            if (date_valid(stu[count].birthday.year, stu[count].birthday.month, stu[count].birthday.day) != 1)
                printf("生日输入有误，请重试！\n\n");
            else
                break;
        }
        printf("修改成功！");
        break;
    case 6:
        printf("请输入新专业:");
        scanf("%s", stu[i].major);
        printf("修改成功！");
        break;
    default:
        printf("取消成功！");
        break;
    }
}

void modi_sid() {
    char temp_sid[15];
    printf("请输入学号：");
    scanf("%s", temp_sid);
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(stu[i].sid, temp_sid) == 0) {
            flag = 1;
            printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
            modi_main(i);
            break;
        }
    }
    if (flag == 0)
        printf("学号不存在！");
}

void modi_name() {
    char temp_name[12];
    printf("请输入姓名：");
    scanf("%s", temp_name);
    int flag = 0;
    int i, j;
    for (i = 0; i < count; i++) {
        if (strcmp(stu[i].name, temp_name) == 0) {
            j = i;
            flag++;
            if (flag == 1) {
                printf("\n|%-4s|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "ID", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            }
            printf("|%-4d", i + 1);
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
        }
    }
    if (flag == 1) {
        modi_main(j);
    } else if (flag > 1) {
        printf("\n查询到多个学生，请输入要修改学生的序号：");
        for (;;) {
            scanf("%d", &i);
            if ((i > 0) && (i < (count + 1))) {
                break;
            }
            printf("输入有误，请重试！");
        }
        modi_main(i - 1);
    } else
        printf("姓名不存在！");
}

void del_sid() {
    char temp_sid[15];
    printf("请输入学号：");
    scanf("%s", temp_sid);
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(stu[i].sid, temp_sid) == 0) {
            flag = 1;
            printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
            printf("\n确认删除此条信息吗？确认请输入Y,取消请输入其他任意字符：");
            char select[1];
            scanf("%s", select);
            if (strcmp(select, "Y") == 0) {
                strcpy(stu[i].sid, stu[count - 1].sid);
                strcpy(stu[i].name, stu[count - 1].name);
                strcpy(stu[i].phone, stu[count - 1].phone);
                strcpy(stu[i].address, stu[count - 1].address);
                stu[i].birthday.year = stu[count - 1].birthday.year;
                stu[i].birthday.month = stu[count - 1].birthday.month;
                stu[i].birthday.day = stu[count - 1].birthday.day;
                strcpy(stu[i].major, stu[count - 1].major);
                count--;
                printf("\n删除成功！\n");
                break;
            } else
                printf("\n取消成功！\n");
            break;
        }
    }
    if (flag == 0)
        printf("学号不存在！\n");
}

void del_name() {
    char temp_name[12];
    printf("请输入姓名：");
    scanf("%s", temp_name);
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(stu[i].name, temp_name) == 0) {
            flag = 1;
            printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
            printf("\n确认删除此条信息吗？确认请输入Y,取消请输入其他任意字符");
            char select[1];
            scanf("%s", select);
            if (strcmp(select, "Y") == 0) {
                strcpy(stu[i].sid, stu[count - 1].sid);
                strcpy(stu[i].name, stu[count - 1].name);
                strcpy(stu[i].phone, stu[count - 1].phone);
                strcpy(stu[i].address, stu[count - 1].address);
                stu[i].birthday.year = stu[count - 1].birthday.year;
                stu[i].birthday.month = stu[count - 1].birthday.month;
                stu[i].birthday.day = stu[count - 1].birthday.day;
                strcpy(stu[i].major, stu[count - 1].major);
                count--;
                printf("\n删除成功！");
                break;
            } else
                printf("\n取消成功！");
            break;
        }
    }
    if (flag == 0)
        printf("姓名不存在！");
}

void sear_sid() {
    char temp_sid[15];
    printf("请输入要查询的学号：");
    scanf("%s", temp_sid);
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(stu[i].sid, temp_sid) == 0) {
            printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        printf("学号未找到！");
    }
}

void sear_name() {
    char temp_name[12];
    printf("请输入要查询的姓名：");
    scanf("%s", temp_name);
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(stu[i].name, temp_name) == 0) {
            if (flag == 0) {
                printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            }
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("姓名未找到！");
    }
}

void sear_bir() {
    struct Date temp_date;
    printf("请输入要查询的生日：");
    scanf("%d%d%d", &temp_date.year, &temp_date.month, &temp_date.day);
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if ((stu[i].birthday.year == temp_date.year) & (stu[i].birthday.month == temp_date.month) & (stu[i].birthday.day == temp_date.day)) {
            if (flag == 0) {
                printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            }
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("生日未找到！");
    }
}

void sear_addr() {
    char temp_addr[12];
    printf("请输入要查询的家庭地址：");
    scanf("%s", temp_addr);
    int flag = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(stu[i].address, temp_addr) == 0) {
            if (flag == 0) {
                printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
            }
            printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
            printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
            printf("%-12s|\n", stu[i].major);
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("家庭地址未找到！");
    }
}

void sear_all() {
    printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
    int i;
    for (i = 0; i < count; i++) {
        printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
        printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
        printf("%-12s|\n", stu[i].major);
    }
}

void count_year() {
    int total = 0, year[100], year_num[100];
    int i, j, flag;
    for (i = 0; i < count; i++) {
        flag = 0;
        for (j = 0; j < total; j++) {
            if (stu[i].birthday.year == year[j]) {
                flag = 1;
                year_num[j]++;
                break;
            }
        }
        if (flag == 0) {
            year[total] = stu[i].birthday.year;
            year_num[total] = 1;
            total++;
        }
    }
    printf("\n|%-6s|%-6s|\n", "Year", "Num");
    for (i = 0; i < total; i++) {
        printf("|%-6d|%-6d|\n", year[i], year_num[i]);
    }
}

void count_major() {
    char major[100][12];
    int major_total = 0, major_num[100];
    int i, j, flag;
    for (i = 0; i < count; i++) {
        flag = 0;
        for (j = 0; j < major_total; j++) {
            if (strcmp(stu[i].major, major[j]) == 0) {
                flag = 1;
                major_num[j]++;
                break;
            }
        }
        if (flag == 0) {
            strcpy(major[major_total], stu[i].major);
            major_num[major_total] = 1;
            major_total++;
        }
    }
    printf("\n|%-12s|%-6s|\n", "Major", "Num");
    for (i = 0; i < major_total; i++) {
        printf("|%-12s|%-6d|\n", major[i], major_num[i]);
    }
}

void sort_sid() {
    struct StuStatus temp_stu;
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = count - 1; j > i; j--) {
            if (strcmp(stu[j].sid, stu[j - 1].sid) < 0) {
                temp_stu = stu[j];
                stu[j] = stu[j - 1];
                stu[j - 1] = temp_stu;
            }
        }
    }
    printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
    for (i = 0; i < count; i++) {
        printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
        printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
        printf("%-12s|\n", stu[i].major);
    }
    printf("\n排序成功！");
}

void sort_name() {
    struct StuStatus temp_stu;
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = count - 1; j > i; j--) {
            if (strcmp(stu[j].name, stu[j - 1].name) < 0) {
                temp_stu = stu[j];
                stu[j] = stu[j - 1];
                stu[j - 1] = temp_stu;
            }
        }
    }
    printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
    for (i = 0; i < count; i++) {
        printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
        printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
        printf("%-12s|\n", stu[i].major);
    }
    printf("\n排序成功！");
}

void sort_major() {
    struct StuStatus temp_stu;
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = count - 1; j > i; j--) {
            if (strcmp(stu[j].major, stu[j - 1].major) < 0) {
                temp_stu = stu[j];
                stu[j] = stu[j - 1];
                stu[j - 1] = temp_stu;
            }
        }
    }
    printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
    for (i = 0; i < count; i++) {
        printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
        printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
        printf("%-12s|\n", stu[i].major);
    }
    printf("\n排序成功！");
}

void sort_year() {
    struct StuStatus temp_stu;
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = count - 1; j > i; j--) {
            if (stu[j].birthday.year < stu[j - 1].birthday.year) {
                temp_stu = stu[j];
                stu[j] = stu[j - 1];
                stu[j - 1] = temp_stu;
            } else if (stu[j].birthday.year == stu[j - 1].birthday.year) {
                if (stu[j].birthday.month < stu[j - 1].birthday.month) {
                    temp_stu = stu[j];
                    stu[j] = stu[j - 1];
                    stu[j - 1] = temp_stu;
                } else if (stu[j].birthday.month == stu[j - 1].birthday.month) {
                    if (stu[j].birthday.day < stu[j - 1].birthday.day) {
                        temp_stu = stu[j];
                        stu[j] = stu[j - 1];
                        stu[j - 1] = temp_stu;
                    }
                }
            }
        }
    }
    printf("\n|%-15s|%-12s|%-15s|%-12s|%-12s|%-12s|\n", "Sid", "Name", "Phone", "Address", "Birthday", "Major");
    for (i = 0; i < count; i++) {
        printf("|%-15s|%-12s|%-15s|%-12s|", stu[i].sid, stu[i].name, stu[i].phone, stu[i].address);
        printf("%-6d%-3d%-3d|", stu[i].birthday.year, stu[i].birthday.month, stu[i].birthday.day);
        printf("%-12s|\n", stu[i].major);
    }
    printf("\n排序成功！");
}

int menu() {
    for (;;) {
        switch (menu_select()) {
        case 1: {
            add();
            break;
        }
        case 2: {
            int select;
            printf("\n         [修改记录子菜单]\n");
            printf("    +------------------------+\n");
            printf("    |    1. 按学号修改       |\n");
            printf("    |    2. 按姓名修改       |\n");
            printf("    |    0. 返回            |\n");
            printf("    +------------------------+\n");
            for (;;) {
                printf("\n请选择(0~2):");
                scanf("%d", &select);
                if (select < 0 || select > 2)
                    printf("选择有误！请重新输入\n");
                else
                    break;
            }
            system("clear");
            switch (select) {
            case 1:
                modi_sid();
                break;
            case 2:
                modi_name();
                break;
            }
            break;
        }
        case 3: {
            int select;
            printf("\n         [删除记录子菜单]\n");
            printf("    +------------------------+\n");
            printf("    |    1. 按学号删除       |\n");
            printf("    |    2. 按姓名删除       |\n");
            printf("    |    0. 返回             |\n");
            printf("    +------------------------+\n");
            for (;;) {
                printf("\n请选择(0~2):");
                scanf("%d", &select);
                if (select < 0 || select > 2)
                    printf("选择有误！请重新输入\n");
                else
                    break;
            }
            system("clear");
            switch (select) {
            case 1:
                del_sid();
                break;
            case 2:
                del_name();
                break;
            }
            break;
        }
        case 4: {
            int select;
            printf("\n         [查询记录子菜单]\n");
            printf("    +------------------------+\n");
            printf("    |    1. 按学号查询       |\n");
            printf("    |    2. 按姓名查询       |\n");
            printf("    |    3. 按生日查询       |\n");
            printf("    |    4. 按家庭地址查询   |\n");
            printf("    |    5. 查询全部         |\n");
            printf("    |    0. 返回             |\n");
            printf("    +------------------------+\n");
            for (;;) {
                printf("\n请选择(0~5):");
                scanf("%d", &select);
                if (select < 0 || select > 5)
                    printf("选择有误！请重新输入\n");
                else
                    break;
            }
            system("clear");
            switch (select) {
            case 1:
                sear_sid();
                break;
            case 2:
                sear_name();
                break;
            case 3:
                sear_bir();
                break;
            case 4:
                sear_addr();
                break;
            case 5:
                sear_all();
                break;
            }
            break;
        }
        case 5: {
            int select;
            printf("\n         [统计记录子菜单]\n");
            printf("    +------------------------+\n");
            printf("    |    1. 按同年统计       |\n");
            printf("    |    2. 按专业统计       |\n");
            printf("    |    0. 返回             |\n");
            printf("    +------------------------+\n");
            for (;;) {
                printf("\n请选择(0~2):");
                scanf("%d", &select);
                if (select < 0 || select > 2)
                    printf("选择有误！请重新输入\n");
                else
                    break;
            }
            system("clear");
            switch (select) {
            case 1:
                count_year();
                break;
            case 2:
                count_major();
                break;
            }
            break;
        }
        case 6: {
            int select;
            printf("\n         [排序记录子菜单]\n");
            printf("    +------------------------+\n");
            printf("    |    1. 按学号排序       |\n");
            printf("    |    2. 按姓名排序       |\n");
            printf("    |    3. 按专业排序       |\n");
            printf("    |    4. 按年龄排序       |\n");
            printf("    |    0. 返回             |\n");
            printf("    +------------------------+\n");
            for (;;) {
                printf("\n请选择(0~4):");
                scanf("%d", &select);
                if (select < 0 || select > 4)
                    printf("选择有误！请重新输入\n");
                else
                    break;
            }
            system("clear");
            switch (select) {
            case 1:
                sort_sid();
                break;
            case 2:
                sort_name();
                break;
            case 3:
                sort_major();
                break;
            case 4:
                sort_year();
                break;
            }
            break;
        }
        case 0: {
            return 0;
        }
        }
    }
}

int main() {
    load();
    menu();
    save();
    return 0;
}