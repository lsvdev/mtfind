#ifndef SEARCH_TASK_H
#define SEARCH_TASK_H

#include "Report.h"
#include <future>

typedef std::packaged_task<std::vector<Match>()> SearchTask_t;

#endif // SEARCH_TASK_H