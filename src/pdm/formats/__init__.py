from __future__ import annotations

from typing import TYPE_CHECKING, cast

from pdm.formats import flit, pipfile, poetry, requirements, setup_py
from pdm.formats.base import MetaConvertError as MetaConvertError

if TYPE_CHECKING:
    from argparse import Namespace
    from pathlib import Path
    from typing import Iterable, Mapping, Protocol, Union

    from pdm.models.candidates import Candidate
    from pdm.models.requirements import Requirement
    from pdm.project import Project

    ExportItems = Union[Iterable[Candidate], Iterable[Requirement]]

    class _Format(Protocol):
        def check_fingerprint(self, project: Project | None, filename: str | Path) -> bool:
            ...

        def convert(
            self,
            project: Project | None,
            filename: str | Path,
            options: Namespace | None,
        ) -> tuple[Mapping, Mapping]:
            ...

        def export(self, project: Project, candidates: ExportItems, options: Namespace | None) -> str:
            ...


FORMATS: Mapping[str, _Format] = {
    "pipfile": cast("_Format", pipfile),
    "poetry": cast("_Format", poetry),
    "flit": cast("_Format", flit),
    "setuppy": cast("_Format", setup_py),
    "requirements": cast("_Format", requirements),
}
