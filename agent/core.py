from __future__ import annotations

from typing import List, Dict, Any


class Agent:
    """Simple task-planning agent."""

    def generate_plan(self, task: str) -> List[str]:
        cleaned = (task or "").strip()
        if not cleaned:
            raise ValueError("Task cannot be empty")

        words = [word for word in cleaned.lower().replace("-", " ").split() if word]
        noun_phrase = " ".join(words[:4]) if words else "task"

        plan = [
            f"Clarify the objective for: {cleaned}",
            f"Break down the work into deliverables for {noun_phrase}",
            f"Execute the highest-priority steps for {noun_phrase}",
            f"Review the result and summarize the outcome of {noun_phrase}",
        ]
        return plan

    def execute(self, task: str) -> Dict[str, Any]:
        cleaned = (task or "").strip()
        if not cleaned:
            raise ValueError("Task cannot be empty")

        plan = self.generate_plan(cleaned)
        summary = (
            f"Completed task planning for '{cleaned}'. "
            f"The plan includes {len(plan)} steps to clarify, execute, and review the work."
        )

        return {
            "status": "completed",
            "task": cleaned,
            "plan": plan,
            "summary": summary,
        }
