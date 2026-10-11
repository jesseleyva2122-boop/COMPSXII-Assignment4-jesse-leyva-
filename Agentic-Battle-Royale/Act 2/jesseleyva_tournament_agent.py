"""Jesse Leyva — Unit 6 tournament export. Evolved genes and complete strategy."""
import random, math
from agents import Agent, INVEST, UNDERCUT

class ImprovedEvolvableAgent(Agent):
    def __init__(self,genes=None,name='Improved Agent'):
        values=[random.random() for _ in range(10)] if genes is None else list(genes)
        if len(values)!=10 or any(not math.isfinite(g) or not 0<=g<=1 for g in values):
            raise ValueError('Expected ten finite genes in [0,1]')
        self.genes=values
        super().__init__(name,'Evolved reciprocity with bounded repair and cautious opponent testing')

    def choose_action(self) -> bool:
        # Keep the complete action logic self-contained for the tournament export.
        def probability(value):
            return 0. if value<.15 else 1. if value>.85 else value
        g=self.genes
        if not self.history:
            return self._apply_noise(random.random()<probability(g[4]))
        window=2+int(g[5]*10)
        recent=self.history[-window:]
        defections=1-sum(recent)/len(recent)
        # Four response genes distinguish retaliation from reconciliation.
        index=(0 if self.my_history[-1] else 2)+(0 if self.history[-1] else 1)
        cooperate=probability(g[index])
        if len(recent)>=window and defections>.25+.60*g[6]:
            cooperate=min(cooperate,probability(g[3]))
        # A scheduled olive branch can break a DD deadlock. Persistent hostile
        # opponents limit repair to one costly offer per interval.
        repair_interval=4+int(g[7]*20)
        if len(self.history)>=3 and not any(self.history[-3:]) and not any(self.my_history[-3:]):
            cooperate=1. if self.round_num%repair_interval==0 else cooperate
        # Probe only long cooperative streaks. The gene can disable probes when
        # irreversible punishers make exploration too expensive.
        probe_interval=12+int(g[8]*40)
        if g[8]<.8 and len(self.history)>=12 and all(self.history[-12:]):
            if self.round_num%probe_interval==0:
                cooperate=0.
        # Require multiple observed responses before treating cooperation as
        # unresponsive. No access to opponent identity, future moves or horizon.
        responses=[self.history[i] for i in range(1,len(self.history))
                   if not self.my_history[i-1]]
        if g[9]>.5 and len(responses)>=4 and sum(responses)/len(responses)>.85:
            cooperate=0.
        return self._apply_noise(random.random()<cooperate)


EVOLVED_GENES = [1.0, 0.10806718135960316, 0.9596804605582223, 0.028486584206704694, 0.8419352739009551, 0.41002771947750827, 0.0, 1.0, 0.9481837114046969, 0.7627127683594422]
TRAINING_CONFIG = {'generations': 35, 'pop_size': 32, 'mutation_rate': 0.28, 'elitism': 2, 'seed': 42}
FINAL_FITNESS = 162.68000000000004
TRAINING_OPPONENTS = ['Always Undercut', 'Always Invest', 'Grim Trigger', 'Tit-for-Tat', 'Pavlov', 'Soft Majority', 'Hard Majority', 'Prober', 'Random (0.1)', 'Random (0.9)']

class JesseLeyvaAgent(ImprovedEvolvableAgent):
    def __init__(self):
        super().__init__(genes=list(EVOLVED_GENES), name="Leyva Adaptive Guard")
        self.student_name = "Jesse Leyva"

def get_agent():
    return JesseLeyvaAgent()

if __name__ == "__main__":
    print(get_agent().name)
