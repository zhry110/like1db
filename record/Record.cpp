//
// Created by zhrys on 2021/11/28.
//

#include "Record.h"
Record::~Record() {
  delete data;
}
void Record::append(const Filed &filed, std::byte *data) {

}
