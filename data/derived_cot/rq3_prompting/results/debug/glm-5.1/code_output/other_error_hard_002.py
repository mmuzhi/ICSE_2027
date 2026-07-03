while i != lca:
    freq[i] += 2  # BUG: should be += 1
    i = parent[i]