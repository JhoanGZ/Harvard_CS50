# Genetic Inheritance Simulation

A person’s blood type is determined by two alleles (i.e., different forms of a gene). The three possible alleles are A, B, and O, of which each person has two (possibly the same, possibly different). Each of a child’s parents randomly passes one of their two blood type alleles to their child. The possible blood type combinations, then, are: OO, OA, OB, AO, AA, AB, BO, BA, and BB.

For example, if one parent has blood type AO and the other parent has blood type BB, then the child’s possible blood types would be AB and OB, depending on which allele is received from each parent. Similarly, if one parent has blood type AO and the other OB, then the child’s possible blood types would be AO, OB, AB, and OO.

The program creates a family tree spanning three generations, simulating the inheritance of alleles for each individual. Each person in the family has two parents and two alleles that determine their blood type. The program uses random assignment to determine the alleles of the first generation and subsequent inheritance rules for following generations.

### Key Features

- **Recursive Family Creation**: Generates family members recursively up to a specified number of generations.
- **Random Allele Assignment**: Assigns blood type alleles (`A`, `B`, or `O`) to each person.
- **Memory Management**: Allocates and deallocates memory dynamically for each person in the family.
