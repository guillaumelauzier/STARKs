#include <libstark/stark.h>

int main() {
  // Define the arithmetic circuit
  std::vector<libstark::FieldElement> input(2);
  libstark::FieldElement x(3);
  libstark::FieldElement y(5);
  input[0] = x;
  input[1] = y;
  libstark::ArithmeticCircuit circuit(input);
  circuit.addOperation(libstark::ADD, 0, 1);

  // Generate the proof
  libstark::ProverParams params(256, 16);
  libstark::Prover prover(params, circuit);
  std::vector<libstark::FieldElement> witness(2);
  witness[0] = x;
  witness[1] = y;
  libstark::ProverWitness proverWitness(witness);
  libstark::Proof proof = prover.generateProof(proverWitness);

  // Verify the proof
  libstark::Verifier verifier(params, circuit);
  bool result = verifier.verify(proof, x + y);
  if (result) {
    std::cout << "Proof verified successfully" << std::endl;
  } else {
    std::cout << "Proof verification failed" << std::endl;
  }
  return 0;
}
