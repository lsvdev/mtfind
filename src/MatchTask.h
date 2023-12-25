#ifndef MATCH_TASK_H
#define MATCH_TASK_H

#include "Report.h"
#include <future>

typedef std::packaged_task<std::vector<Match>()> MatchTask_t;

#endif