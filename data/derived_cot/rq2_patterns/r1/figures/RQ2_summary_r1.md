# RQ2 结果总结（r1）

本总结基于 r1 模型的 RQ2 输出结果（pass/fail 为主标签，judge 仅作辅助）。

## 1. 数据覆盖
- 分析样本总数：1690
- 任务覆盖：generation / execution / debug / translation
- 具备测试标签的样本：1688

参考文件：
- `RQ2/segmented_pattern_results/r1/figures/analysis_numbers.json`

## 2. 全局层面（pass vs fail）

结论：失败 CoT 更长、更冗余、token 更多，且更偏 PU/SD/MR/KR，验证与落地类节点（VV/CC/AUX）占比更低。

关键数据：
- 平均长度（raw）：pass 18.41，fail 21.89（+3.48）
- 压缩比：pass 0.6997，fail 0.6387（-0.0610）
- 平均 token：pass 5824，fail 9037（+3212）
- 类别分布（pass -> fail）：
  - PU: 0.164 -> 0.234（+0.070）
  - SD: 0.134 -> 0.183（+0.049）
  - MR: 0.092 -> 0.126（+0.034）
  - VV: 0.318 -> 0.192（-0.126）
  - CC: 0.061 -> 0.035（-0.026）
  - AUX: 0.068 -> 0.033（-0.035）

对应图：
- `RQ2/segmented_pattern_results/r1/figures/global_valid_vs_invalid_metrics.svg`
- `RQ2/segmented_pattern_results/r1/figures/global_category_dist.svg`
- `RQ2/segmented_pattern_results/r1/figures/global_token_count_comparison.svg`
- `RQ2/segmented_pattern_results/r1/figures/global_token_range.svg`
- `RQ2/segmented_pattern_results/r1/figures/topology_diff_fail_minus_pass.svg`

## 3. 任务画像（单模型 r1）

说明：以下画像全部基于 r1 单模型的 pass vs fail 对比，不涉及跨模型对比。

### 3.1 generation
- pass 321 / fail 121
- 平均长度：pass 28.07，fail 47.74（+19.68）
- 压缩比：pass 0.7345，fail 0.6051（-0.1294）
- 平均 token：pass 11012，fail 25074（+14062）
- 结构变化：SD 明显上升（+0.1309），VV 下降（-0.0328）

解读：失败显著“过度规划+验证不足”，并且出现极端冗长链。

### 3.2 execution
- pass 200 / fail 177
- 平均长度：pass 6.40，fail 10.48（+4.09）
- 压缩比：pass 0.7438，fail 0.6591（-0.0847）
- 平均 token：pass 1075，fail 2348（+1272）
- 结构变化：VV 大幅下降（-0.1572），SD 上升（+0.0287）

解读：失败主要表现为验证不足，转而堆叠理解/反思。

### 3.3 debug
- pass 443 / fail 56
- 平均长度：pass 18.40，fail 24.98（+6.58）
- 压缩比：pass 0.6489，fail 0.5822（-0.0668）
- 平均 token：pass 4120，fail 7030（+2910）
- 结构变化：VV 下降（-0.0358），PU/IP 上升

解读：失败偏向“诊断拉长”，复测不足。

### 3.4 translation
- pass 203 / fail 167
- 平均长度：pass 15.02，fail 14.22（-0.80）
- 压缩比：pass 0.7120，fail 0.6603（-0.0517）
- 平均 token：pass 6019，fail 5179（-840）
- 结构变化：VV 下降（-0.0177），IP 上升

解读：翻译失败更像“流程缩短导致缺验证/落地”。

对应图：
- `RQ2/segmented_pattern_results/r1/figures/by_task_delta_len_raw.svg`
- `RQ2/segmented_pattern_results/r1/figures/by_task_delta_compress_ratio.svg`
- `RQ2/segmented_pattern_results/r1/figures/by_task_delta_token_count.svg`
- `RQ2/segmented_pattern_results/r1/figures/by_task_delta_sd_vv.svg`
- `RQ2/segmented_pattern_results/r1/figures/heatmap_task_x_category_delta.svg`

## 4. judge vs test（辅助分析）

整体趋势：judge 高召回、低特异，偏向“判 valid”。

- overall：precision 0.768，recall 0.947，specificity 0.361
- generation：precision 0.84，recall 0.981，specificity 0.504
- execution：precision 0.679，recall 0.835，specificity 0.554
- debug：precision 0.911，recall 0.975，specificity 0.25
- translation：precision 0.557，recall 0.941，specificity 0.090

对应图：
- `RQ2/segmented_pattern_results/r1/figures/confusion_error_rates_by_task.svg`

## 5. 典型反 pattern（基于 fail vs pass）

重点以 fail vs pass 为主表，FP/FN 仅作辅助解释。

对应表格：
- 全局：
  - `RQ2/segmented_pattern_results/r1/figures/top_patterns_fail_vs_pass_global_by_p_value.svg`
  - `RQ2/segmented_pattern_results/r1/figures/top_patterns_fail_vs_pass_global_by_abs_delta.svg`
- 分任务：
  - `RQ2/segmented_pattern_results/r1/figures/top_patterns_fail_vs_pass_by_task_by_p_value.svg`
  - `RQ2/segmented_pattern_results/r1/figures/top_patterns_fail_vs_pass_by_task_by_abs_delta.svg`

辅助表格（judge 误判分析）：
- `RQ2/segmented_pattern_results/r1/figures/top_patterns_fp_vs_tp_*`
- `RQ2/segmented_pattern_results/r1/figures/top_patterns_fn_vs_tn_*`

## 6. 总结一句话
失败 CoT 不是“想得不够”，而是“想得太多但缺少验证与落地”：规划与反思占比上升、验证与产出下降，且这一趋势在 generation/execution/debug 中尤为明显，translation 则表现为过短导致验证缺失。
