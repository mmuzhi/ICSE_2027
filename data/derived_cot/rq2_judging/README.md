# RQ2 Judging Results

Structure:

- `<cot_model>/<judge_model>/<task>_judge_results.jsonl`: raw judge votes.
- `<cot_model>/aggregated_<task>.json`: weighted-vote aggregation over judge models.
- `<cot_model>/cot_vs_test_analysis.json`: comparison between aggregated CoT validity and test results.

Current judge model slugs: `deepseekv3.2`, `gemini-3-flash-preview`, `glm5.1`.
