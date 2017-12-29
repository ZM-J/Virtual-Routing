#include "args.h"

std::shared_ptr<Args> Args::m_args = nullptr;

Args::Args() {}
Args::~Args() { Args::m_args = nullptr; }

std::shared_ptr<Args> Args::getInstance(void) {
    if (m_args == nullptr) m_args = std::shared_ptr<Args>(new Args());
    return m_args;
}