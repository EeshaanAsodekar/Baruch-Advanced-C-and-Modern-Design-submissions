#include "ShapeComposite.h"
void Print(const ShapeComposite& sc, std::ostream& os) {
    os << sc;
}
// Subquestion (d) mod 6.10
void ShapeComposite::Accept(ShapeVisitor& sv) {
	sv.Visit(*this);
};