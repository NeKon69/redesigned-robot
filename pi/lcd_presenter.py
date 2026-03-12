from __future__ import annotations

from pi.models import DeliveryJob


def idle_lines(buffer_text: str, queue_size: int) -> list[str]:
    return [
        buffer_text[:20],
        "Enter cab#box##",
        f"Queue: {queue_size}",
        "*=back D=clear",
    ]


def moving_lines(job: DeliveryJob, remaining: int) -> list[str]:
    return [
        f"Cabinet {job.cabinet_id}",
        f"Box {job.box_id}",
        "Moving...",
        f"Left: {remaining}",
    ]


def waiting_card_lines(job: DeliveryJob, remaining: int) -> list[str]:
    return [
        f"Cabinet {job.cabinet_id}",
        f"Box {job.box_id}",
        "Scan card",
        f"Left: {remaining}",
    ]


def access_denied_lines(job: DeliveryJob, remaining: int) -> list[str]:
    return [
        f"Cabinet {job.cabinet_id}",
        f"Box {job.box_id}",
        "Access denied",
        f"Left: {remaining}",
    ]


def waiting_box_lines(job: DeliveryJob, remaining: int) -> list[str]:
    return [
        f"Cabinet {job.cabinet_id}",
        f"Box {job.box_id}",
        "Insert box",
        f"Left: {remaining}",
    ]


def waiting_handoff_lines(job: DeliveryJob, remaining: int) -> list[str]:
    return [
        f"Cabinet {job.cabinet_id}",
        f"Box {job.box_id}",
        "Waiting handoff",
        f"Left: {remaining}",
    ]


def returning_home_lines(remaining: int) -> list[str]:
    return ["Delivery done", "Returning home", "", f"Queue: {remaining}"]
