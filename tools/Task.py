import math

MAX_TIME = 1440


class Task:
    def __init__(self, task_id: int, deadline: int, duration: int, perfect_benefit: float) -> None:
        """ Creates a new task with the corresponding task_id, deadline,
        duration, and perfect_benefit.

        Args:
        - task_id (int): task id of the Task
        - deadline (int): deadline of the Task
        - duration (int): duration of the Task
        - perfect_benefit (float): the benefit recieved from
        completing the Task anytime before (or on) the deadline

        Output:
        - Task object: corresponding Task object

        >>> task0 = Task(0, 1, 2, 3.0)
        >>> print(task0)
        Task 0 has deadline 1, duration 2, and max benefit 3.0
        """
        self.task_id = task_id
        self.deadline = deadline
        self.duration = duration
        self.perfect_benefit = perfect_benefit

    def get_late_benefit(self, minutes_late: int) -> int:
        """
        Returns the benefit recieved from completing this task
        minutes_late minutes late
        Sample usage:
        >>> task0 = Task(0, 1, 2, 3.0)
        >>> task0.get_late_benefit(0)
        3.0
        >>> task0.get_late_benefit(5)
        2.7555368532043722
        >>> task0.get_late_benefit(30)
        1.8014867364367977
        """
        minutes_late = max(0, minutes_late)
        return self.perfect_benefit * math.exp(-0.0170 * minutes_late)

    def get_benefit(self, completion_time: int) -> int:
        """
        >>> task0 = Task(0, 1, 2, 3.0)
        >>> task0.get_benefit(0)
        3.0
        >>> task0.get_benefit(1)
        3.0
        >>> task0.get_benefit(6)
        2.7555368532043722
        >>> task0.get_benefit(1441)
        0
        """
        if completion_time > MAX_TIME:
            return 0
        return self.get_late_benefit(completion_time - self.deadline)

    def __str__(self):
        """
        Generates a readable string representation of a task
        Sample usage:
        >>> task0 = Task(0, 1, 2, 3.0)
        >>> str(task0)
        'Task 0 has deadline 1, duration 2, and max benefit 3.0'
        """
        return "Task {} has deadline {}, duration {}, and max benefit {}".format(self.task_id, self.deadline, self.duration, self.perfect_benefit)
