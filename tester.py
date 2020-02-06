"""
THIS FILE was created originally by Jonathan Stein and then edited by Connor Tremblay.
All credit is due to them and I claim no part in the creation of the code unless edited.
"""
import pandas as pd
import plotly.express as px
from subprocess import run

def parse(stdout, stderr):
    # return a tuple of time as an float, and the value For me thats
    return (float(stdout.decode()), float(stderr.decode().split('\n')[0][5:]))

def output(data):
    df = pd.DataFrame(data)
    df['speedup'] = df.time[0]/df.time
    df['efficency'] = df['speedup']/df.threads
    speedup_graph = px.line(df, x='threads', y='speedup')
    efficency_graph = px.line(df, x='threads', y='efficency')
    speedup_file = open('speedup_graph.html', 'w')
    efficency_file = open('efficency_graph.html', 'w')
    speedup_file.write(speedup_graph.to_html())
    efficency_file.write(efficency_graph.to_html())
    df.to_pickle('output_data.df')
    speedup_file.close()
    efficency_file.close()

if __name__ == "__main__":
    a, b, num_iters = map(float, input("a, b, num_iters space separated: ").split())
    data = []
    try:
        for threads in range(1, 37):
            cmd = f"srun -N 1 --mem=8G --cpus-per-task=24 time -p ./integrate {a} {b} {num_iters} {threads}"
            print(cmd)
            ran = run(cmd.split(), capture_output=True)
            value, time = parse(ran.stdout, ran.stderr)
            data.append({
                "threads": threads,
                "time": time,
                "value": value,
                })
    except Exception as e:
        pd.DataFrame(data).to_pickle('err_out.txt')
        raise e
    except KeyboardInterrupt:
        pd.DataFrame(data).to_pickle('err_out.txt')
    else:
        output(data)
