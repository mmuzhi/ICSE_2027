# Derived CoT Data Layout

This directory stores all model-generated CoT traces and paper-related intermediate results.

## Structure

- `rq1_traces/`
  Raw CoT collection outputs for generation, execution, debugging, and translation.
- `rq1_segmented/`
  Segmented reasoning-action traces used by RQ1, RQ2, and RQ3.
- `rq1_analysis/`
  Optional saved outputs from the remaining RQ1 analysis scripts.
- `rq2_judging/`
  Judge-model outputs and aggregated validity labels.
- `rq2_patterns/`
  Pattern-mining outputs and RQ2 summaries.
- `rq2_eval/`
  Evaluation files used to compare judge outputs with task correctness.
- `rq3_task_classification/`
  Saved classifier outputs for RQ3.1.
- `rq3_prompting/`
  Baseline and pattern-guided prompting outputs for RQ3.2.
- `rq3_early_stopping/`
  Early-stopping outputs and evaluation files for RQ3.3.

## Rule

Keep code under `rq1_macro_patterns/`, `rq2_micro_patterns/`, and `rq3_applications/`.
Keep generated artifacts and intermediate experiment results under `data/derived_cot/`.
