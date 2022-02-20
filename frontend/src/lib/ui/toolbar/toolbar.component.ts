import {AfterViewInit, Component, ElementRef, Input, ViewChild} from '@angular/core';

@Component({
    selector: 'toolbar',
    templateUrl: './toolbar.component.html',
    styleUrls: ['./toolbar.component.scss'],
})
export class ToolbarComponent implements AfterViewInit {
    @Input()
    title: String;

    @ViewChild("titleElement")
    titleElement: ElementRef;

    ngAfterViewInit(): void {
        this.titleElement.nativeElement.setAttribute("data-glitch", this.title);
    }
}