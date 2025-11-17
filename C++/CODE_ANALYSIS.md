# C++ Labs – Code Analysis

## LABA1_3sem — Array intersection utility
**Implementation overview**
- `Array` owns a dynamically allocated `int*` and implements constructors, copy semantics, manual input/output helpers, and an `intersect` method that deduplicates the intersection values between two arrays before returning a new `Array` object.
- `main.cpp` builds an array of `Array` objects, reads user input for each, prints them, and iteratively intersects all arrays to compute the common set of elements.

**Notable issues / risks**
- `Array` manually manages raw memory without defining a move constructor/assignment operator, so temporaries returned from `intersect` rely on implicit shallow moves that may cause double frees if the compiler chooses move semantics.
- `main.cpp` explicitly calls `result.~Array()` on a stack object, leading to undefined behavior when the destructor runs again as the variable goes out of scope.

## LABA2_3sem — Custom `MyString` class
**Implementation overview**
- `MyString` reimplements much of `std::string`: constructors, copy control, concatenation, substring extraction via `operator()`, comparison operators that compare string lengths, arithmetic-like operators, and increment/decrement operators that shift character codes.
- `main.cpp` exercises the API via console I/O and includes `SetConsoleOutputCP` calls for Windows-specific UTF-8 output.

**Notable issues / risks**
- The header unconditionally includes `windows.h`, making the class non-portable and preventing successful compilation on non-Windows platforms.
- The indexing operators skip bounds checks, exposing undefined behavior when callers pass invalid indices.
- As in LABA1, `main.cpp` manually calls `str1.~MyString()`, double-destroying the object.

## LABA3_3sem — Transport vehicle hierarchy (arrays)
**Implementation overview**
- Defines a polymorphic `TransportVehicle` base class that computes travel time and transport costs and exposes virtual `print_*` helpers plus mutators/accessors.
- Three derived classes (`Car`, `Bicycle`, `Cart`) override table-printing helpers with type-specific labels.
- `main.cpp` dynamically allocates arrays of each vehicle type, prints a consolidated table, and provides a menu for editing and running calculations on an individual object.

**Notable issues / risks**
- Manual allocation of raw `new[]` arrays with matching `delete[]` calls; any early `return` paths (e.g., invalid type selection) must delete all three arrays to avoid leaks.
- The interactive menu uses recursion-like loops but lacks validation around every numeric input, so entering non-numeric data will leave `cin` in a failed state without recovery.

## LABA4_3sem — Transport vehicle hierarchy (deque-backed)
**Implementation overview**
- Rebuilds the LABA3 transport hierarchy with a richer virtual interface (`clone`, `type_name`, formatted displays) and stores base-class pointers inside a custom templated `Deque` implemented as a doubly linked list.
- The UI drives CRUD operations over the deque, supports cost calculations, linear search by name, and bubble-sort ordering via pointer swaps.

**Notable issues / risks**
- `Deque` defines neither copy nor move semantics; copying a deque (accidentally or intentionally) will yield double deletes when destructors of the shallow copies run.
- The container stores owning raw pointers without smart-pointer wrappers, so every insertion must be balanced by a manual `delete` (some paths—e.g., unsuccessful edits that throw—can still leak).
- Several operations (e.g., `findByName`) depend on default-constructed `TransportVehicle` temporaries and string equality, so name comparisons are case-sensitive and cannot handle locale-specific normalization.

## LABA5_3sem — Placeholder
- Contains only the default CMake target and `main.cpp` that prints "Hello, World!", indicating the lab has not been implemented yet.
