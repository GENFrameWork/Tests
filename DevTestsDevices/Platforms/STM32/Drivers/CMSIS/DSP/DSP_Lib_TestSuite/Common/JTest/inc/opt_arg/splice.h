#pragma once

#define SPLICE(a,b) SPLICE_1(a,b)
#define SPLICE_1(a,b) SPLICE_2(a,b)
#define SPLICE_2(a,b) a##b

