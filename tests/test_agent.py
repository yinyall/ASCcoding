import unittest

from agent.core import Agent


class AgentTests(unittest.TestCase):
    def test_generate_plan_creates_multiple_steps(self):
        agent = Agent()
        result = agent.generate_plan("Build a landing page for a product launch")

        self.assertIsInstance(result, list)
        self.assertGreater(len(result), 1)
        self.assertTrue(all(isinstance(step, str) and step for step in result))

    def test_execute_returns_completed_summary(self):
        agent = Agent()
        result = agent.execute("Prepare a draft release note")

        self.assertEqual(result["status"], "completed")
        self.assertIn("release", result["summary"].lower())
        self.assertIn("plan", result)

    def test_empty_task_raises_value_error(self):
        agent = Agent()

        with self.assertRaises(ValueError):
            agent.execute("   ")


if __name__ == "__main__":
    unittest.main()
