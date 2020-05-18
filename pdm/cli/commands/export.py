import argparse
from pathlib import Path

from pdm.cli.commands.base import BaseCommand
from pdm.cli.options import sections_group
from pdm.formats import FORMATS
from pdm.iostream import stream
from pdm.project import Project


class Command(BaseCommand):
    """Export the locked packages set to other formats"""

    def add_arguments(self, parser: argparse.ArgumentParser) -> None:
        parser.add_argument(
            "-f",
            "--format",
            choices=FORMATS.keys(),
            default="requirements",
            help="Specify the export file format",
        )
        sections_group.add_to_parser(parser)
        parser.add_argument(
            "--without-hashes",
            dest="hashes",
            action="store_false",
            default=True,
            help="Don't include artifact hashes",
        )
        parser.add_argument(
            "-o",
            "--output",
            help="Write output to the given file, or print to stdout if not given",
        )

    def handle(self, project: Project, options: argparse.Namespace) -> None:
        candidates = []
        if options.default:
            # Don't include self candidate
            temp = project.get_locked_candidates()
            temp.pop(project.meta.name)
            candidates.extend(temp.values())
        if options.dev:
            candidates.extend(project.get_locked_candidates("dev").values())
        for section in options.sections:
            candidates.extend(project.get_locked_candidates(section).values())
        content = FORMATS[options.format].export(project, candidates, options)
        if options.output:
            Path(options.output).write_text(content)
        else:
            stream.echo(content)
