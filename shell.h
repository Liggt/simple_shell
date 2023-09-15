#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_SYSTEM_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define MAX_HISTORY_ENTRIES 4096

extern char **environ;

typedef struct StringNode {
    int num;
    char *str;
    struct StringNode *next;
} StringNode;

typedef struct ShellInfo {
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    StringNode *env;
    StringNode *history;
    StringNode *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} ShellInfo;

#define SHELL_INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

typedef struct BuiltinCommand {
    char *type;
    int (*func)(ShellInfo *);
} BuiltinCommand;

int ShellLoop(ShellInfo *, char **);
int FindBuiltinCommand(ShellInfo *);
void FindCommand(ShellInfo *);
void ForkCommand(ShellInfo *);

int IsCommand(ShellInfo *, char *);
char *DuplicateChars(const char *, int, int);
char *FindPath(ShellInfo *, char *, char *);

int LoopShell(char **);

void PrintError(const char *);
int PrintCharacter(int);
int WriteToFD(int, char);
int WriteStringToFD(int, const char *);

int StringLength(const char *);
int StringCompare(const char *, const char *);
char *StartsWith(const char *, const char *);
char *StringConcatenate(const char *, const char *);

char *StringCopy(char *, const char *);
char *StringDuplicate(const char *);
void PrintString(const char *);
int PrintCharacter(int);

char *StringNCopy(char *, const char *, int);
char *StringNCat(char *, const char *, int);
char *StringChar(const char *, char);

char **StringTokenize(char *, const char *);
char **StringTokenize2(char *, const char *);

char *MemorySet(char *, char, unsigned int);
void FreeStrings(char **);
void *ReallocateMemory(void *, unsigned int, unsigned int);

int FreeBlock(void **);

int AtoiInteractive(ShellInfo *);
int IsDelimiter(char, const char *);
int IsAlpha(int);
int Atoi(const char *);

int ErrorAtoi(const char *);
void PrintErrorWithInfo(ShellInfo *, const char *);
int PrintDecimal(int, int);
char *ConvertNumber(long int, int, int);
void RemoveComments(char *);

int ExitShell(ShellInfo *);
int ChangeDirectory(ShellInfo *);
int DisplayHelp(ShellInfo *);

int DisplayHistory(ShellInfo *);
int DisplayAlias(ShellInfo *);

ssize_t GetInput(ShellInfo *);
int GetLine(ShellInfo *, char **, size_t *);
void HandleSigint(int);

void ClearShellInfo(ShellInfo *);
void SetShellInfo(ShellInfo *, char **);
void FreeShellInfo(ShellInfo *, int);

char *GetEnvironmentVariable(ShellInfo *, const char *);
int DisplayEnvironment(ShellInfo *);
int SetEnvironmentVariable(ShellInfo *);
int UnsetEnvironmentVariable(ShellInfo *);
int PopulateEnvironmentList(ShellInfo *);

char **GetEnvironment(ShellInfo *);
int UnsetEnvVariable(ShellInfo *, char *);
int SetEnvVariable(ShellInfo *, char *, char *);

char *GetHistoryFile(ShellInfo *info);
int WriteShellHistory(ShellInfo *info);
int ReadShellHistory(ShellInfo *info);
int BuildHistoryList(ShellInfo *info, char *buf, int linecount);
int RenumberHistory(ShellInfo *info);

StringNode *AddStringNode(StringNode **, const char *, int);
StringNode *AddStringNodeEnd(StringNode **, const char *, int);
size_t PrintStringList(const StringNode *);
int DeleteStringNodeAtIndex(StringNode **, unsigned int);
void FreeStringList(StringNode **);

size_t StringListLength(const StringNode *);
char **StringListToStrings(StringNode *);
size_t PrintStringList(const StringNode *);
StringNode *NodeStartsWith(StringNode *, char *, char);
ssize_t GetNodeIndex(StringNode *, StringNode *);

#endif

