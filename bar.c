// Copyright 2025 Daniel Pfeifer <daniel@pfeifer-mail.de>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

#include "bar.h"
#include <qux.h>

char* bar(char const* x)
{
  return qux("hello", x);
}

void bar_free(char* str)
{
  qux_free(str);
}
