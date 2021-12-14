#include <torch/csrc/jit/ir/ir.h>

namespace torch {
namespace jit {

TORCH_API void FuseInferenceOpsForSparseNN(
    std::shared_ptr<torch::jit::Graph>& graph);

TORCH_API void EliminateTrivialEquallySplit(
    std::shared_ptr<torch::jit::Graph>& graph);

TORCH_API void FuseListUnpack(std::shared_ptr<torch::jit::Graph>& graph);

// If outputs_are_immutable is set to false, don't replace the view ops that
// produce aliases of graph outputs with the copy version.
TORCH_API void ReplaceWithCopy(
    std::shared_ptr<torch::jit::Graph>& graph,
    bool outputs_are_immutable = true);

TORCH_API void EnableStaticRuntimeLayerNorm(
    std::shared_ptr<torch::jit::Graph>& graph);

TORCH_API void RemoveImmutableInputDictLookups(
    std::shared_ptr<torch::jit::Graph>& graph);

TORCH_API bool HasInplaceOp(
    std::shared_ptr<Graph>& graph,
    const AliasDb& alias_db);

TORCH_API bool forwardHasOp(const Module& module, const char* op_name);

TORCH_API void FuseSignLog1P(std::shared_ptr<Graph>& graph);

TORCH_API void UseVariadicTupleUnpack(const std::shared_ptr<Graph>& graph);

// c10::Symbol::fromQualString is a bit long to type everywhere, and
// we can't use a `using` statement since it's a static class function.
inline c10::Symbol fromQualString(const std::string& qual_string) {
  return c10::Symbol::fromQualString(qual_string);
}

// [Create owned refs for returned constants]
// StaticRuntimeBlockRunner moves its outputs to the return value at the end of
// run_impl. However, there's a corner case where this can cause problems. If
// we return a constant, then the only reference in the constants_ array can
// be destroyed by this move.
// We could add special logic to handle this in run_impl. But since this is a
// relatively rare corner case, it's simpler to just add an op that does nothing
// but create an owned reference to its input. This owned reference can be
// safely moved out of StaticRuntimeBlockRunner.
void CreateOwnedRefs(Graph& graph);

TORCH_API void UseVariadicGroupedAccessor(const std::shared_ptr<Graph>& graph);

} // namespace jit
} // namespace torch
