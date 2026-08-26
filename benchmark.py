"""
Benchmark para o solver TSP.

Executa o algoritmo N vezes por instância com seeds aleatórias controladas,
registrando custo inicial, custo final, melhoria percentual e tempo de execução.

Uso:
    python3 benchmark.py

Saída:
    benchmark_results.csv
"""

import csv
import os
import random
import subprocess
import time
from pathlib import Path

# ── Configurações ─────────────────────────────────────────────────────────────
EXECUTABLE   = "./tsp"
INSTANCES_DIR = Path("instancias")
OUTPUT_FILE  = "benchmark_results.csv"
NUM_RUNS     = 10   # execuções por instância
# ──────────────────────────────────────────────────────────────────────────────


def parse_output(output: str) -> dict:
    """Extrai seed, custo inicial e custo final do stdout do programa."""
    result = {"seed": None, "custo_inicial": None, "custo_final": None}
    parsing_inicial = False
    parsing_final   = False

    for line in output.splitlines():
        line = line.strip()
        if line.startswith("Seed:"):
            result["seed"] = int(line.split(":")[1].strip())
        elif "Solucao inicial" in line:
            parsing_inicial, parsing_final = True, False
        elif "Solucao final" in line:
            parsing_inicial, parsing_final = False, True
        elif line.startswith("Latência Total (MLP Cost):"):
            try:
                cost = float(line.split(":")[1].strip())
                if parsing_inicial:
                    result["custo_inicial"] = cost
                    parsing_inicial = False
                elif parsing_final:
                    result["custo_final"] = cost
                    parsing_final = False
            except ValueError:
                pass

    return result


def run_benchmark():
    if not os.path.exists(EXECUTABLE):
        print(f"Erro: executável '{EXECUTABLE}' não encontrado. Compile primeiro.")
        return

    instances = sorted(INSTANCES_DIR.glob("*.tsp"))
    if not instances:
        print(f"Erro: nenhuma instância .tsp encontrada em '{INSTANCES_DIR}'.")
        return

    fieldnames = [
        "Instancia", "Run", "Seed",
        "Custo_Inicial", "Custo_Final",
        "Melhoria_(%)", "Tempo_Execucao_(s)"
    ]
    avg_fieldnames = [
        "Instancia", "Custo_Inicial_Medio", "Custo_Final_Medio",
        "Melhoria_Media_(%)", "Tempo_Execucao_Medio_(s)"
    ]

    with open(OUTPUT_FILE, "w", newline="") as f, \
         open("benchmark_averages.csv", "w", newline="") as f_avg:
        
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        
        avg_writer = csv.DictWriter(f_avg, fieldnames=avg_fieldnames)
        avg_writer.writeheader()

        for instance in instances:
            print(f"\n{'─'*50}")
            print(f"Instância: {instance.name}  ({NUM_RUNS} execuções)")
            print(f"{'─'*50}")
            
            soma_inicial = 0
            soma_final = 0
            soma_melhoria = 0
            soma_tempo = 0
            valid_runs = 0

            for run_idx in range(1, NUM_RUNS + 1):
                seed = random.randint(1, 9_999_999)

                start = time.perf_counter()
                try:
                    proc = subprocess.run(
                        [EXECUTABLE, str(instance), str(seed)],
                        capture_output=True, text=True, check=True
                    )
                except subprocess.CalledProcessError as e:
                    print(f"  Run {run_idx:2d} | seed {seed} | ERRO: {e}")
                    continue
                elapsed = time.perf_counter() - start

                parsed = parse_output(proc.stdout)

                if parsed["custo_inicial"] is None or parsed["custo_final"] is None:
                    print(f"  Run {run_idx:2d} | seed {seed} | Não foi possível extrair custos.")
                    print("  Saída:", proc.stdout)
                    continue

                melhoria = round(
                    (parsed["custo_inicial"] - parsed["custo_final"])
                    / parsed["custo_inicial"] * 100, 2
                )

                print(
                    f"  Run {run_idx:2d} | seed {parsed['seed']:>8} | "
                    f"inicial: {int(parsed['custo_inicial']):>7} | "
                    f"final: {int(parsed['custo_final']):>7} | "
                    f"melhoria: {melhoria:>6.2f}% | "
                    f"tempo: {elapsed:.4f}s"
                )

                writer.writerow({
                    "Instancia":          instance.name,
                    "Run":                run_idx,
                    "Seed":               parsed["seed"],
                    "Custo_Inicial":      int(parsed["custo_inicial"]),
                    "Custo_Final":        int(parsed["custo_final"]),
                    "Melhoria_(%)":       melhoria,
                    "Tempo_Execucao_(s)": round(elapsed, 6),
                })
                
                soma_inicial += int(parsed["custo_inicial"])
                soma_final += int(parsed["custo_final"])
                soma_melhoria += melhoria
                soma_tempo += elapsed
                valid_runs += 1

            if valid_runs > 0:
                avg_writer.writerow({
                    "Instancia": instance.name,
                    "Custo_Inicial_Medio": int(soma_inicial / valid_runs),
                    "Custo_Final_Medio": int(soma_final / valid_runs),
                    "Melhoria_Media_(%)": round(soma_melhoria / valid_runs, 2),
                    "Tempo_Execucao_Medio_(s)": round(soma_tempo / valid_runs, 6),
                })

    print(f"\n{'═'*50}")
    print(f"Resultados salvos em: {OUTPUT_FILE}")
    print(f"Médias salvas em: benchmark_averages.csv")
    print(f"{'═'*50}")


if __name__ == "__main__":
    run_benchmark()
