# Multi-Agent Grid2Op Example

> **Author**: RTE (https://www.rte-france.com)  
> **License**: [Mozilla Public License 2.0](http://mozilla.org/MPL/2.0/)  
> **Part of**: Grid2Op – A platform to model sequential decision-making in power systems.

---

## 📘 Overview

This example demonstrates how to set up and interact with a **multi-agent environment** in [Grid2Op](https://github.com/rte-france/Grid2Op).  
You’ll learn how to:

- Initialize a centralized Grid2Op environment.
- Define per-agent control and observation domains.
- Wrap it into a `MultiAgentEnv` for decentralized interactions.
- Run an episode using random agent actions.

---

## 📦 Prerequisites

Ensure you have `grid2op` installed:

```bash
pip install grid2op
```

---

## 🧠 Code Walkthrough

### 🔧 1. Centralized Environment Setup

```python
import grid2op
from grid2op.multi_agent import MultiAgentEnv

env_name = "l2rpn_case14_sandbox"
cent_env = grid2op.make(env_name)
```

Initializes the centralized environment using the predefined `"l2rpn_case14_sandbox"` scenario.

---

### 👥 2. Multi-Agent Configuration

#### Controlled Substations (Action Domains)

```python
action_domains = {
    "agent_0": [0, 1, 2, 3, 4],
    "agent_1": [5, 6, 7, 8, 9, 10, 11, 12, 13]
}
```

Each agent has control over a specific set of substations.

#### Observed Substations (Observation Domains)

```python
observation_domains = {
    "agent_0": [0, 1, 2, 3, 4, 5, 8, 6],
    "agent_1": [5, 6, 7, 8, 9, 10, 11, 12, 13, 4, 3]
}
```

Each agent receives observations from a subset of substations, which may overlap.

---

### 🧩 3. Multi-Agent Environment Initialization

```python
env = MultiAgentEnv(
    cent_env,
    action_domains=action_domains,
    observation_domains=observation_domains
)
```

Wraps the centralized environment into a multi-agent interface.

---

### ▶️ 4. Simulation Run

#### Environment Reset

```python
dict_obs = env.reset()
```

Returns a dictionary of observations, keyed by agent names:

```python
{
  "agent_0": SubGridObservation,
  "agent_1": SubGridObservation
}
```

#### Sampling Agent Actions

```python
act = {
    "agent_0": env.action_spaces["agent_0"].sample(),
    "agent_1": env.action_spaces["agent_1"].sample()
}
```

Each agent samples a random action from its respective action space.

#### Environment Step

```python
dict_obs, dict_reward, dict_done, dict_info = env.step(act)
```

- `dict_obs`: Next observation per agent.
- `dict_reward`: Scalar reward per agent.
- `dict_done`: Boolean flag indicating if the episode is over for each agent.
- `dict_info`: Auxiliary info per agent.

#### Output Logs

```python
print(f"stepped ... \n dict_obs={dict_obs} \n dict_reward={dict_reward} \n dict_done={dict_done} \n dict_info={dict_info}")
```

---

### 🧹 5. Cleanup

```python
env.close()
cent_env.close()
```

Always close the environments to release resources properly.

---

## 📝 Full Script

```python
# Copyright (c) 2019-2022, RTE
# SPDX-License-Identifier: MPL-2.0

import grid2op
from grid2op.multi_agent import MultiAgentEnv
import pdb

if __name__ == "__main__":
    env_name = "l2rpn_case14_sandbox"
    cent_env = grid2op.make(env_name)

    action_domains = {
        "agent_0": [0, 1, 2, 3, 4],
        "agent_1": [5, 6, 7, 8, 9, 10, 11, 12, 13]
    }

    observation_domains = {
        "agent_0": [0, 1, 2, 3, 4, 5, 8, 6],
        "agent_1": [5, 6, 7, 8, 9, 10, 11, 12, 13, 4, 3]
    }

    env = MultiAgentEnv(
        cent_env,
        action_domains=action_domains,
        observation_domains=observation_domains
    )

    dict_obs = env.reset()

    act = {
        "agent_0": env.action_spaces["agent_0"].sample(),
        "agent_1": env.action_spaces["agent_1"].sample()
    }

    dict_obs, dict_reward, dict_done, dict_info = env.step(act)

    print(f"stepped ... \n dict_obs={dict_obs} \n dict_reward={dict_reward} \n dict_done={dict_done} \n dict_info={dict_info}")

    env.close()
    cent_env.close()
```

---

## 📚 References

- [Grid2Op Documentation](https://grid2op.readthedocs.io/)
- [Grid2Op GitHub](https://github.com/rte-france/Grid2Op)
- [L2RPN Sandbox](https://github.com/rte-france/Grid2Op/tree/master/l2rpn_case14_sandbox)

---

## 🔐 License

This example is distributed under the [Mozilla Public License v2.0](http://mozilla.org/MPL/2.0/).  
See `AUTHORS.txt` and SPDX header for full details.
