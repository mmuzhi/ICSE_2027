import math

def similarity(vector1, vector2):
    dotProduct = 0.0
    norm1 = 0.0
    norm2 = 0.0
    for i in range(len(vector1)):
        dotProduct += vector1[i] * vector2[i]
        norm1 += vector1[i] * vector1[i]
        norm2 += vector2[i] * vector2[i]
    denominator = math.sqrt(norm1) * math.sqrt(norm2)
    if denominator == 0:
        return 0.0
    return dotProduct / denominator

def cosineSimilarities(vector1, vectorsAll):
    norm1_sq = _dotProduct(vector1, vector1)
    if norm1_sq == 0:
        return [0.0] * len(vectorsAll)
    norm1 = math.sqrt(norm1_sq)
    similarities = []
    for vector2 in vectorsAll:
        norm2_sq = _dotProduct(vector2, vector2)
        if norm2_sq == 0:
            similarities.append(0.0)
        else:
            norm2 = math.sqrt(norm2_sq)
            dot_prod = _dotProduct(vector1, vector2)
            denominator = norm1 * norm2
            sim = dot_prod / denominator
            similarities.append(sim)
    return similarities

def nSimilarity(vectorList1, vectorList2):
    if not vectorList1 or not vectorList2:
        raise ValueError("At least one of the passed lists is empty.")
    avgVector1 = _averageVector(vectorList1)
    avgVector2 = _averageVector(vectorList2)
    return similarity(avgVector1, avgVector2)

def computeIdfWeightDict(totalNum, numberDict):
    result = {}
    for key, count in numberDict.items():
        weight = math.log((totalNum + 1) / (count + 1))
        result[key] = weight
    return result

def _dotProduct(vector1, vector2):
    result = 0.0
    for i in range(len(vector1)):
        result += vector1[i] * vector2[i]
    return result

def _averageVector(vectors):
    n = len(vectors[0])
    avgVector = [0.0] * n
    for vector in vectors:
        for i in range(n):
            avgVector[i] += vector[i]
    for i in range(n):
        avgVector[i] /= len(vectors)
    return avgVector