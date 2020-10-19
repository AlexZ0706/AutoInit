#include "auto_init.h"

//定义表示函数，用以自动初始化搜索分段
static int rti_start(void)
{
    return 0;
}
INIT_EXPORT(rti_start, "0");

static int rti_board_start(void)
{
    return 0;
}
INIT_EXPORT(rti_board_start, "0.end");

static int rti_board_end(void)
{
    return 0;
}
INIT_EXPORT(rti_board_end, "1.end");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end, "6.end");

//level 1 函数列表初始化
void level1_init(void)
{
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__auto_init_rti_board_start; fn_ptr < &__auto_init_rti_board_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
}

//level 2-6 函数列表初始化
void level2_6_init(void)
{
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__auto_init_rti_board_end; fn_ptr < &__auto_init_rti_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }
}
