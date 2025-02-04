////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2016, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory.
// Written by the LBANN Research Team (B. Van Essen, et al.) listed in
// the CONTRIBUTORS file. <lbann-dev@llnl.gov>
//
// LLNL-CODE-697807.
// All rights reserved.
//
// This file is part of LBANN: Livermore Big Artificial Neural Network
// Toolkit. For details, see http://software.llnl.gov/LBANN or
// https://github.com/LLNL/LBANN.
//
// Licensed under the Apache License, Version 2.0 (the "Licensee"); you
// may not use this file except in compliance with the License.  You may
// obtain a copy of the License at:
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied. See the License for the specific language governing
// permissions and limitations under the license.
////////////////////////////////////////////////////////////////////////////////

#ifndef LBANN_SGD_TRAINING_ALGORITHM_HPP
#define LBANN_SGD_TRAINING_ALGORITHM_HPP

#include "lbann/execution_algorithms/training_algorithm.hpp"
#include "lbann/execution_contexts/execution_context.hpp"
#include "lbann/execution_contexts/sgd_execution_context.hpp"
#include "lbann/utils/cloneable.hpp"

namespace lbann {

/** @brief Base class for LBANN SGD-family training algorithms. */
class sgd_training_algorithm
  : public Cloneable<sgd_training_algorithm, training_algorithm>
{
  using BaseType = Cloneable<sgd_training_algorithm, training_algorithm>;

public:
  /** @brief Construct with a name. */
  sgd_training_algorithm(std::string name) : BaseType{std::move(name)} {}

  sgd_training_algorithm(const sgd_training_algorithm& other) = default;
  sgd_training_algorithm&
  operator=(const sgd_training_algorithm& other) = default;
  sgd_training_algorithm(sgd_training_algorithm&& other) = default;
  sgd_training_algorithm& operator=(sgd_training_algorithm&& other) = default;

  virtual ~sgd_training_algorithm() = default;
  /** Copy training_algorithm. */
  //  virtual sgd_training_algorithm* copy() const = default;

  std::string get_type() const override;

  // ===========================================
  // Execution
  // ===========================================

  /** Apply the training algorithm to the model with the provided
      context and execution mode */
  void apply(execution_context& c,
             model& model,
             data_coordinator& dc,
             execution_mode mode,
             termination_criteria const& term_criteria) override;

  /** Train a model using an iterative SGD solver. */
  void train(sgd_execution_context& c,
             model& model,
             data_coordinator& dc,
             size_t num_epochs,
             size_t num_batches = 0);

  /** Evaluate a model using the forward pass of an SGD solver. */
  void evaluate(sgd_execution_context& c,
                model& model,
                data_coordinator& dc,
                execution_mode mode,
                size_t num_batches = 0);

protected:
  /** Train model on one step / mini-batch of an SGD forward pass */
  virtual bool train_mini_batch(sgd_execution_context& c,
                                model& model,
                                data_coordinator& dc);

  /** Evaluate model on one step / mini-batch of an SGD forward pass */
  virtual bool evaluate_mini_batch(sgd_execution_context& c,
                                   model& model,
                                   data_coordinator& dc,
                                   execution_mode mode);

  ////////////////////////////////////////////////////////////
  // Callbacks
  ////////////////////////////////////////////////////////////

  /** Execute callbacks at start of training. */
  virtual void do_train_begin_cbs(model& model);
  /** Execute callbacks at end of training. */
  virtual void do_train_end_cbs(model& model);
  /** Execute callbacks at start of evaluation. */
  virtual void do_evaluate_begin_cbs(model& model, execution_mode mode);
  /** Execute callbacks at end of evaluation. */
  virtual void do_evaluate_end_cbs(model& model, execution_mode mode);
  /** Execute callbacks at start of epoch. */
  virtual void do_epoch_begin_cbs(model& model);
  /** Execute callbacks at end of epoch. */
  virtual void do_epoch_end_cbs(model& model);
  /** Execute callbacks at start of mini-batch. */
  virtual void do_batch_begin_cbs(model& model, execution_mode mode);
  /** Execute callbacks at end of mini-batch. */
  virtual void do_batch_end_cbs(model& model, execution_mode mode);
};

} // namespace lbann

#endif // LBANN_SGD_TRAINING_ALGORITHM_HPP
