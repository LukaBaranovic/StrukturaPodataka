/*
Header file za postavljanje slova u trie strukturu.
*/

#pragma once

#include <stdio.h>
#include "declaration.h"


position create_child(position, char);
position append_brother(position, char);