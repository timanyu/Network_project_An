#pragma once

#include"../../public.h"

MYSQL* LinkDataBase();

MYSQL_RES *Query(char *sql);//查询

void FreeRes(MYSQL_RES *res);

void UnLinkDataBase();

int GetRows(MYSQL_RES *res);

MYSQL_ROW GetRow(MYSQL_RES *res);

int UpData(char *sql);//更新数据