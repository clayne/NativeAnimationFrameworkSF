#pragma once
#include "PNode.h"
#include "Animation/PoseCache.h"
#include "Animation/IAnimationFile.h"

namespace Animation::Procedural
{
	class PGraph : public IAnimationFile
	{
	public:
		inline static constexpr size_t MAX_DEPTH{ 100 };
		using InstanceData = PEvaluationContext;

		std::vector<std::unique_ptr<PNode>> nodes;
		std::vector<PNode*> sortedNodes;
		uint64_t actorNode = 0;

		bool SortNodes();
		void InsertCacheReleaseNodes();
		std::span<ozz::math::SoaTransform> Evaluate(InstanceData& a_graphInst, PoseCache& a_poseCache);
		void AdvanceTime(InstanceData& a_graphInst, float a_deltaTime);
		void Synchronize(InstanceData& a_graphInst, InstanceData& a_ownerInst, PGraph* a_ownerGraph, float a_correctionDelta);
		void InitInstanceData(InstanceData& a_graphInst);
		void PointersToIndexes();
		virtual std::unique_ptr<Generator> CreateGenerator() override;

	private:
		bool DepthFirstNodeSort(PNode* a_node, size_t a_depth, std::unordered_set<PNode*>& a_visited, std::unordered_set<PNode*>& a_recursionStack);
	};
}