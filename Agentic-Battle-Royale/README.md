# Assignment 4: Agentic Battle Royale — Jesse Leyva

Open **[the completed Unit 6 notebook](Act%202/unit_6_tournament.ipynb)**. It includes saved execution outputs for single-elimination and round-robin, matchup tables, five-seed sensitivity checks, 180 supplemental baseline games, and a 500–1000-word reflection at the bottom.

## Provenance and roster
This project continues [Assignment 3](https://github.com/jesseleyva2122-boop/COMPSVIII-Assignment3-jesse-leyva-) and includes its previous notebooks and agent export. This folder is hosted in the existing C Assignment 4 repository selected by Jesse; it is not a new fork of Assignment 3. Leyva Adaptive Guard is the unchanged Unit 5 Python export. No retraining or tournament-time strategy changes were made.

The instructor replacement `student_agents` folder was not available. The assignment-permitted existing starter roster is used: King kong, My Evolved Agent, and Leyva Adaptive Guard. These are **three-agent starter tournaments**, not a claim about full class-wide results.

## Main executed results
Seed 2026; 100 rounds per match; three round-robin repetitions (18 ordered-pair games). My Evolved Agent won both formats. Leyva Adaptive Guard ranked second with 1,574 points; strict win rate 1/12 (8.3%), ten ties and one loss. The notebook explains the differing ranking and win-rate denominators and the bracket tie rule.

## Run again
```bash
cd 'Act 2'
python -m pip install -r requirements.txt
python -m pip install -r requirements-notebook.txt
jupyter notebook unit_6_tournament.ipynb
```
Choose Run All. Run from `Act 2` so relative imports and roster paths resolve. Seeds are fixed for reproducibility. Saved notebook cells were executed sequentially through real in-process IPython because this execution environment blocks kernel socket creation; captured outputs and execution counts are retained, and no results were fabricated.

Evidence: [raw tournament results](Act%202/tournament_results.json), [analysis data](Act%202/unit6_analysis_results.json), [bracket](Act%202/tournament_bracket.png), and [interactive dashboard](Act%202/tournament_dashboard.html) (download and open the HTML locally).

The Unit 4 and Unit 5 notebooks remain available for review. Supplemental tests evaluate the existing agent; they do not alter the official roster or its recorded main results.
