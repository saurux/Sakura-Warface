#pragma once

template <typename T>
T VirtualFunction(void* general, int index) { return (*(T**)general)[index]; }