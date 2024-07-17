#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll infinito = 1e18;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;

vector<vector<ll>> mancha;
vector<vector<ii>> vizinhos;
vector<ll> tanque;
bitset<100010> percorrido;

void dijkstra(int visto, ll nmr_cidades, ll tanque_cheio)
{
    for (ll i = 1; i <= nmr_cidades; i++)
        mancha[visto][i] = tanque[i] = infinito;

    tanque[visto] = tanque_cheio;
    mancha[visto][visto] = 0;
    percorrido.reset();

    priority_queue<iii, vector<iii>, greater<iii>> heap;
    heap.push(iii(0, -tanque_cheio, visto));

    while (!heap.empty())
    {
        auto [x, y, u] = heap.top();
        heap.pop();

        if (percorrido.test(u))
            continue;

        percorrido.set(u);

        for (const auto &[v, custo] : vizinhos[u])
        {
            if (custo <= tanque[u] && (mancha[visto][v] > mancha[visto][u] || (mancha[visto][v] == mancha[visto][u] && tanque[u] - custo > tanque[v])))
            {
                mancha[visto][v] = mancha[visto][u];
                tanque[v] = tanque[u] - custo;
                heap.push(iii(mancha[visto][v], -tanque[v], v));
            }

            if (custo <= tanque_cheio && (mancha[visto][v] > mancha[visto][u] + 1 || (mancha[visto][v] == mancha[visto][u] + 1 && tanque_cheio - custo > tanque[v])))
            {
                mancha[visto][v] = mancha[visto][u] + 1;
                tanque[v] = tanque_cheio - custo;
                heap.push(iii(mancha[visto][v], -tanque[v], v));
            }
        }
    }
}

vector<ll> solucao(ll nmr_cidades, ll tanque_cheio, const vector<ii> &consultas)
{
    vector<ll> respostas(consultas.size());
    mancha.assign(nmr_cidades + 1, vector<ll>(nmr_cidades + 1, infinito));
    tanque.assign(nmr_cidades + 1, infinito);

    for (int j = 1; j <= nmr_cidades; j++)
        dijkstra(j, nmr_cidades, tanque_cheio);

    for (size_t i = 0; i < consultas.size(); i++)
    {
        ll x = consultas[i].first;
        ll y = consultas[i].second;

        if (mancha[x][y] == infinito)
            respostas[i] = -1;
        else
            respostas[i] = mancha[x][y];
    }

    return respostas;
}

int main()
{
    ll nmr_cidades, estradas, tanque_cheio, nmr_consultas;
    cin >> nmr_cidades >> estradas >> tanque_cheio;

    vizinhos.resize(nmr_cidades + 1);

    for (ll i = 0; i < estradas; i++)
    {
        ll u, v, custo;
        cin >> u >> v >> custo;
        vizinhos[u].emplace_back(v, custo);
        vizinhos[v].emplace_back(u, custo);
    }

    cin >> nmr_consultas;

    vector<ii> consultas(nmr_consultas);

    for (ll i = 0; i < nmr_consultas; i++)
        cin >> consultas[i].first >> consultas[i].second;

    vector<ll> respostas = solucao(nmr_cidades, tanque_cheio, consultas);

    for (ll resposta : respostas)
        cout << resposta << endl;

    return 0;
}