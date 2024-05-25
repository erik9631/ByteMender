//
// Created by erik9 on 5/25/2024.
//

#pragma once

struct HeapEntry {
    unsigned long long address = 0;
    unsigned long long size = 0;
    unsigned long long flags = 0;
    unsigned long long processId = 0;
};