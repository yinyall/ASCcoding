from __future__ import annotations

import argparse
import json

from .core import Agent


def main() -> None:
    parser = argparse.ArgumentParser(description="Run the ASC task-planning agent")
    parser.add_argument("--task", required=True, help="Task description to plan and execute")
    args = parser.parse_args()

    agent = Agent()
    result = agent.execute(args.task)
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
