#include "iconFactory.h" // d

Icon IconFactory::createStaticIcon() {
    return {{ Cell(BLUE, "▇") }};
}

Icon IconFactory::createDynamicIcon() {
    return {{ Cell(RED, "▇") }};
}

// { Cell(RED, "▇") } 代表一個一維的 Cell 陣列
// {{ Cell(RED, "▇") }} 代表一個二維的 Cell 陣列




