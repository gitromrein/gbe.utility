import xml.etree.ElementTree as ET
import sys

def remove_failure_blocks(input_file, output_file):
    # Lade das XML-Dokument
    tree = ET.parse(input_file)
    root = tree.getroot()

    # Iteriere durch alle <testsuite>-Elemente und entferne <failure>-Elemente
    for testsuite in root.findall(".//testsuite"):
        # Gehe durch alle <testcase>-Elemente innerhalb jedes <testsuite>-Elements
        for testcase in testsuite.findall("testcase"):
            failure = testcase.find("failure")
            if failure is not None:
                # Entferne das <failure>-Tag, falls es existiert
                testcase.remove(failure)

    # Speichere die bearbeitete XML-Datei
    tree.write(output_file, encoding="utf-8", xml_declaration=True)
    print(f"Erfolgreich alle <failure>-Blöcke aus {input_file} entfernt und in {output_file} gespeichert.")

if __name__ == "__main__":
    # Prüfe, ob die richtigen Parameter übergeben wurden
    if len(sys.argv) != 3:
        print("Usage: python remove_failures.py <input_file> <output_file>")
    else:
        input_file = sys.argv[1]  # Erste Kommandozeilen-Argument (Eingabedatei)
        output_file = sys.argv[2]  # Zweites Kommandozeilen-Argument (Ausgabedatei)
        remove_failure_blocks(input_file, output_file)
