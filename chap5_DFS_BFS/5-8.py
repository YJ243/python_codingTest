# DFS �޼��� ����
def dfs(graph, v, visited):
    # ���� ��带 �湮 ó��
    visited[v] = True
    print(v, end=' ')
    # ���� ���� ����� �ٸ� ��带 ��������� �湮
    for i in graph[v]:
        if not visited[i]:
            dfs(graph, i, visited)

# 