#pragma once

#include <unordered_set>
#include "common/singleton.h"
#include "dag/logical_dag.h"
#include "dag/physical_dag.h"
#include "procedures/dag_procedure.h"
#include "narray/narray.h"

namespace minerva {

class ExpandEngine;
class PhysicalEngine;
class DataStore;
class ThreadPool;
class ImplDecider;

class MinervaSystem :
  public EverlastingSingleton<MinervaSystem> {
  friend class NArray;
  friend class EverlastingSingleton<MinervaSystem>;
 public:
  ~MinervaSystem();
  void Initialize(int* argc, char*** argv);
  void Finalize();
  LogicalDag& logical_dag() { return logical_dag_; }
  PhysicalDag& physical_dag() { return physical_dag_; }
  DataStore& data_store() { return *data_store_; }
  PhysicalEngine& physical_engine() { return *physical_engine_; }

  void SetImplDecider(ImplDecider* );
  void Eval(NArray& narr);
  float* GetValue(NArray& narr);

 private:
  DISALLOW_COPY_AND_ASSIGN(MinervaSystem);
  MinervaSystem();
  void LoadBuiltinDagMonitors();
  void IncrExternRC(LogicalDag::DNode* , int amount = 1);

 private:
  LogicalDag logical_dag_;
  PhysicalDag physical_dag_;

  ExpandEngine* expand_engine_;
  PhysicalEngine* physical_engine_;
  DataStore* data_store_;

  std::unordered_set<uint64_t> extern_rc_changed_ldnodes_;
};

} // end of namespace minerva
